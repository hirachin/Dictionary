#pragma once
# include <Siv3D.hpp>

class DoubleClicker
{
	Key m_key;

	Stopwatch m_timer;

	int m_count;

	int m_timeout_ms = 200;

	bool m_isDoubleClicked;

public:

	DoubleClicker(const Key& _key) :m_key(_key), m_count(0), m_isDoubleClicked(false) {}

	void update()
	{
		m_isDoubleClicked = false;

		if (m_timer.isActive() && m_timer.ms() > m_timeout_ms)
		{
			m_timer.reset();
			m_count = 0;
		}

		if (m_key.released)
		{
			m_timer.start();
			m_count++;
		}

		if (m_count == 2)
		{
			m_isDoubleClicked = true;
			m_timer.reset();
			m_count = 0;
		}
	}

	int getCount()const
	{
		return m_count;
	}

	bool isDoubleClicked()const
	{
		return m_isDoubleClicked;
	}
};