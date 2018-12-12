#include "pch.h"
#include "TextItem.h"

void TextItem::operator=(TextItem other)
{
	m_char = other.m_char;
	m_colour = other.m_colour;
}
