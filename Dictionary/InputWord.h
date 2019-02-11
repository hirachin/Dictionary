#pragma once
# include <Siv3D.hpp>

class InputWord
{
	String m_text;
	String m_fontName;

	Size m_size;
	bool m_hasChanged;

	PlusCombinedKeys m_copyKey;

	bool m_isEnabled;

public:

	InputWord() {}

	InputWord(const String& _fontName, const Size& _size, bool _enabled = true) :m_fontName(_fontName), m_size(_size),
		m_hasChanged(false), m_copyKey(Input::KeyControl + Input::KeyV), m_isEnabled(_enabled)
	{

	}

	void clear()
	{
		m_text.clear();
	}

	String getText()const { return m_text; }
	bool hasChanged()const { return m_hasChanged; }

	bool isEmpty()const { return m_text.isEmpty; }

	void setEnabled(bool _enabled)
	{
		m_isEnabled = _enabled;
	}

	bool isEnabled()const { return m_isEnabled; }

	void update()
	{
		m_hasChanged = false;

		if (!m_isEnabled) { return; }
		if (Input::KeyTab.pressed || Input::KeyEnter.pressed) { return; }


		const String preText = m_text;

		Input::GetCharsHelper(m_text);

		if (m_copyKey.clicked)
		{
			const String clipboardText = Clipboard::GetText();

			if (!clipboardText.isEmpty)
			{
				m_text += clipboardText;
			}
		}

		if (m_text != preText)
		{
			m_hasChanged = true;
		}
	}

	void draw(const Point& _pos)const
	{
		Rect(_pos, m_size).drawFrame(2, 0, m_isEnabled?Palette::Blue:Palette::Black);
		FontAsset(m_fontName)(m_text).draw(_pos.movedBy(10, 0), Palette::Black);

		if (!m_isEnabled)
		{
			return;
		}



		const Rect wordRegion = FontAsset(m_fontName)(m_text).region(_pos.movedBy(10, 0));
		const Point cursorPos = _pos.movedBy(10, 0).movedBy(wordRegion.w, 0);
		const int offsetY = 5;

		if (InRange<int>(Time::GetMillisec() % 1500, 0, 750))
		{
			Rect(cursorPos.movedBy(5, offsetY), Size(3, m_size.y - offsetY * 2)).draw(Palette::Black);

		}



	}

	void draw(int _x, int _y)const
	{
		draw(Point(_x, _y));
	}
};