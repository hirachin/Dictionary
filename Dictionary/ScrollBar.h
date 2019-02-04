#pragma once
# include <Siv3D.hpp>

class ScrollBar
{
	Point m_pos;
	Size m_size;

	Rect m_knob;


	int m_rangeBegin;
	int m_rangeEnd;

	int m_value;

	bool m_isGrabbed;

	std::pair<int, int> getKnobYRange()const
	{
		return std::make_pair(getBarColider().pos.y, getBarColider().pos.y + getBarColider().size.y - m_knob.size.y);
	}



public:

	ScrollBar() {}

	ScrollBar(int _begin, int _end, const Point& _pos, const Size& _size) :
		m_rangeBegin(_begin), m_rangeEnd(_end), m_pos(_pos), m_size(_size),
		m_isGrabbed(false), m_value(_begin)
	{
		setKnob();
	}

	ScrollBar(int _begin, int _end, int _initValue,const Point& _pos, const Size& _size) :
		m_rangeBegin(_begin), m_rangeEnd(_end), m_pos(_pos), m_size(_size),
		m_isGrabbed(false), m_value(_begin)
	{
		setKnob();
		setValue(_initValue);
	}

	void setKnob()
	{
		m_knob = Rect(m_pos, m_size.x, static_cast<int>(m_size.y /Clamp<double>((m_rangeEnd - m_rangeBegin + 1)/1.7, 1, 3)));
	}

	void setValue(int _value)
	{
		if (!InRange(_value, m_rangeBegin, m_rangeEnd) || m_rangeEnd == m_rangeBegin)
		{
			return;
		}

		m_value = _value;

		const double scale = static_cast<double>(m_value - m_rangeBegin) / (m_rangeEnd - m_rangeBegin);

		m_knob.pos.y = m_pos.y + static_cast<int>(scale*(m_size.y - m_knob.size.y));
	}

	void setRangeBegin(int _begin)
	{
		if (m_rangeEnd < _begin)
		{
			m_rangeBegin = m_rangeEnd;
		}
		else
		{
			m_rangeBegin = _begin;
		}

		setKnob();
		setValue(Clamp(m_value, m_rangeBegin, m_rangeEnd));
	}

	void setRangeEnd(int _end)
	{
		if (m_rangeBegin > _end)
		{
			m_rangeEnd = m_rangeBegin;
		}
		else
		{
			m_rangeEnd = _end;
		}

		setKnob();
		setValue(Clamp(m_value, m_rangeBegin, m_rangeEnd));
	}

	int getValue()const
	{
		return m_value;
	}

	Rect getBarColider()const
	{
		return Rect(m_pos, m_size);
	}

	void move(int _move)
	{
		if (_move == 0 || m_isGrabbed) { return; }

		setValue(m_value + _move);
	}

	void update()
	{
		if (getBarColider().intersects(Mouse::Pos()) && Input::MouseL.pressed)
		{
			m_isGrabbed = true;
		}

		else if (Input::MouseL.released)
		{
			m_isGrabbed = false;
		}

		if(m_isGrabbed && m_rangeEnd != m_rangeBegin)
		{
			m_knob.setCenter(m_knob.center.x,Mouse::Pos().y);

			m_knob.pos.y = Clamp(m_knob.pos.y, getKnobYRange().first, getKnobYRange().second);

			const double scale = static_cast<double>(m_knob.pos.y - m_pos.y) / (m_size.y - m_knob.size.y);

			m_value = m_rangeBegin + static_cast<int>(scale*(m_rangeEnd - m_rangeBegin));

		}
	}

	void draw()const
	{
		Rect(m_pos, m_size).drawFrame(0, 2, Palette::Black);
		m_knob.draw(Palette::Gray);
	}

};
