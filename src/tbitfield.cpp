#include "tbitfield.h"

TBitField::TBitField(int len)
{
  BitLen = len;
	MemLen = (len - 1) / 32 + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
  delete[]pMem;

}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return n / 32;
}


TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  int v;
	v = n % 32;
	TELEM tmp = 1;
	tmp = tmp << v;
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] &=~(GetMemMask(n));
}

bool TBitField::GetBit(const int n) const // получить значение бита
{
	return pMem[GetMemIndex(n)&GetMemMask(n)];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		if (MemLen!=bf.MemLen)
		{
			MemLen = bf.MemLen;
			delete[]pMem;
			pMem = new TELEM[MemLen];
		}
		
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return false;
	}
	for (int i = 0; i < MemLen-1; i++)
	{
		if (pMem[i]!=bf.pMem[i])
		{
			return false;
		}
	}
	for (int i = (MemLen-1)*32; i < BitLen; i++)
	{
		if (GetBit(i)!=bf.GetBit(i))
		{
			return false;
		}
	}
	return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf) {
		return false;
	}
  else
  {
	  return true;
  }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

istream &operator>>(istream &is, TBitField &bf) {
	char c;
	int k = 0;
	do
	{
		is >> c;
		if (c == '1')
		{
			bf.SetBit(k);
		}
		if (c == '0')
		{
			bf.ClrBit(k);
		}
	} while ((c == '1') || (c == '0'));
	return is;
}

ostream &operator<<(ostream &os, const TBitField &bf) {
	for (int i = 0; i < bf.BitLen; i++)
	{
		os << bf.GetBit(i) << " ";
	}
	return os;
}