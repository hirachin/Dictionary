#pragma once
# include "SceneBase.h"
# include "Dictionary.h"
# include "InputWord.h"

class AddWord :public MyApp::Scene
{
	InputWord m_inputEnglish;
	InputWord m_inputJapanese;

	Table m_table;
	KeyMover m_keyMover;
	ScrollBar m_scrollBar;

	Array<std::pair<String, String>> m_inputDatas;

	PlusCombinedKeys m_addKey = PlusCombinedKeys(Input::KeyControl, Input::KeyEnter);

	int m_cursor = 0;
	int m_initIdx = 0;

	bool addData()
	{
		if (m_inputEnglish.isEmpty() || m_inputJapanese.isEmpty()) { return false; }

		m_inputDatas.emplace_back(m_inputEnglish.getText(), m_inputJapanese.getText());
		m_inputEnglish.clear();
		m_inputJapanese.clear();
		m_initIdx = 0;
		m_scrollBar.setRangeEnd(m_inputDatas.size() - 1);

		m_cursor = 0;
		m_inputEnglish.setEnabled(true);
		m_inputJapanese.setEnabled(false);
		return true;
	}

	void init()override
	{
		m_inputEnglish = InputWord(L"wordFont", Size(300, 50));
		m_inputJapanese = InputWord(L"wordFont", Size(300, 50),false);
		m_table = Table();
		m_keyMover = KeyMover(Input::KeyDown, Input::KeyUp);
		m_scrollBar = ScrollBar(0, 0, Point(610, 100), Size(20, 300));

	}

	void update()override
	{
		m_keyMover.update();
		m_scrollBar.update();

		if (Input::KeyTab.clicked)
		{
			m_cursor += 1;
			m_cursor %= 2;

			switch (m_cursor)
			{
				case 0:
				{
					m_inputEnglish.setEnabled(true);
					m_inputJapanese.setEnabled(false);
					break;
				}

				case 1:
				{
					m_inputEnglish.setEnabled(false);
					m_inputJapanese.setEnabled(true);
					break;
				}
			}
		}

		if (m_addKey.clicked)
		{
			addData();
		}

		const int move = m_keyMover.getKeyMove() + Mouse::Wheel();

		if (move != 0)
		{
			m_initIdx += move;
			m_initIdx = Clamp<int>(m_initIdx, 0, m_inputDatas.size() - 1);

			m_scrollBar.setValue(m_initIdx);
		}
		else
		{
			m_initIdx = Clamp<int>(m_scrollBar.getValue(), 0, m_inputDatas.size() - 1);
		}

		m_inputEnglish.update();
		m_inputJapanese.update();
	}

	void draw()const override
	{
		m_inputEnglish.draw(10, 20);
		m_inputJapanese.draw(Window::Width() / 2 + 10, 20);
		
		Line(0, 90, Window::Width(), 90).draw(Palette::Black);
		m_table.draw(Point(10,100),m_inputDatas,m_initIdx);
		m_scrollBar.draw();
	}
};