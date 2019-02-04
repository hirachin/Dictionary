#pragma once
# include <Siv3D.hpp>

class KeyMover
{
	Key m_plusKey;
	Key m_minusKey;

	int m_keyMove;

	int m_intervalCount;
	int m_INTERVAL;


public:

	KeyMover() {}

	KeyMover(const Key& _plusKey, const Key& _minusKey) :m_plusKey(_plusKey), m_minusKey(_minusKey),
		m_keyMove(0), m_intervalCount(0), m_INTERVAL(8) {}

	void update()
	{
		m_keyMove = 0;

		const int keyMove = m_plusKey.pressed - m_minusKey.pressed;

		m_intervalCount--;
		if (keyMove != 0 && m_intervalCount <= 0)
		{
			m_keyMove += keyMove;
			m_intervalCount = m_INTERVAL;
		}

		if (m_plusKey.released || m_minusKey.released)
		{
			m_intervalCount = 0;
		}
	}

	int getKeyMove()const
	{
		return m_keyMove;
	}

};