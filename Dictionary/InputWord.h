#pragma once
# include <Siv3D.hpp>

class InputWord
{
	String m_text;
	String m_fontName;

	Size m_size;
	bool m_hasChanged;

	PlusCombinedKeys m_COPYKEY;

public:

	InputWord() {}

	InputWord(const String& _fontName, const Size& _size) :m_fontName(_fontName), m_size(_size),
		m_hasChanged(false),m_COPYKEY(Input::KeyControl + Input::KeyV)
	{

	}

	void clear()
	{
		m_text.clear();
	}

	String getText()const { return m_text; }
	bool hasChanged()const { return m_hasChanged; }

	void update()
	{
		const String preText = m_text;
		m_hasChanged = false;

		Input::GetCharsHelper(m_text);

		if (m_COPYKEY.clicked)
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
		Rect(_pos, m_size).drawFrame(2, 0, Palette::Black);
		FontAsset(m_fontName)(m_text).draw(_pos.movedBy(10, 0), Palette::Black);
	}

	void draw(int _x, int _y)const
	{
		draw(Point(_x, _y));
	}
};