#pragma once
# include "DictionarySearch.h"
# include "InputWord.h"
# include "Dictionary.h"
# include "KeyMover.h"
# include "Table.h"
# include "ScrollBar.h"

class DictionarySearch : public MyApp::Scene
{
	
	InputWord m_inputWord;
	KeyMover m_keyMover;
	ScrollBar m_scrollBar;


	Dictionary m_dictionary;
	Table m_table;

	int m_initIdx;
	Array<std::pair<String, String>> m_searchResult;

	PlusCombinedKeys m_scrollRightKey = PlusCombinedKeys(Input::KeyControl, Input::KeyRight);
	PlusCombinedKeys m_scrollLeftKey = PlusCombinedKeys(Input::KeyControl, Input::KeyLeft);

	void setSearchResult(const Array<std::pair<String, String>>& _result)
	{
		m_initIdx = 0;
		m_searchResult = _result;
		m_scrollBar.setRangeEnd(m_searchResult.size() - 1);
		m_scrollBar.setValue(m_initIdx);
	}

	void search()
	{
		if (m_inputWord.getText().isEmpty)
		{
			setSearchResult(m_dictionary.getDatas());
			return;
		}

		setSearchResult(m_dictionary.search(m_inputWord.getText()));
	}

	void scrollTable()
	{
		const int move = m_keyMover.getKeyMove() + Mouse::Wheel();

		if (move != 0)
		{
			m_initIdx += move;
			m_initIdx = Clamp<int>(m_initIdx, 0, m_searchResult.size() - 1);
			m_scrollBar.setValue(m_initIdx);
		}
		else
		{
			m_initIdx = Clamp<int>(m_scrollBar.getValue(), 0, m_searchResult.size() - 1);
		}
	}

public:

	void init()override
	{
		m_inputWord = InputWord(L"wordFont", Size(300, 50));
		m_keyMover = KeyMover(Input::KeyDown, Input::KeyUp);
		m_dictionary = Dictionary();
		m_table = Table();
		m_scrollBar = ScrollBar(0, 0, Point(610, 100), Size(20, 300));

		loadFromConfig();
		m_dictionary.sortAndDeleteDuplication();

		search();
	}

	void update()override
	{
		m_keyMover.update();
		m_inputWord.update();
		m_scrollBar.update();

		scrollTable();

		/*
		if (Input::KeyF5.clicked)
		{
			Println(L"reload");
			m_dictionary.reload();
		}
		*/

		if (m_inputWord.hasChanged())
		{
			Println(L"change");
			search();
		}

		if (m_scrollLeftKey.clicked || m_scrollRightKey.clicked)
		{
			changeScene(L"AddWord",500);
		}

	}

	void draw()const override
	{

		m_inputWord.draw(50, 20);
		Line(0, 90, Window::Width(), 90).draw(Palette::Black);
		m_table.draw(Point(10, 100), m_searchResult, m_initIdx);
		m_scrollBar.draw();
	}

	void loadFromConfig()
	{
		TextReader reader(L"config");

		String line;
		while (reader.readLine(line))
		{
			if (FileSystem::IsFile(line) && FileSystem::Extension(line) == L"csv")
			{
				m_dictionary.load(line);
			}
			else
			{
				Println(line, L"is not found or not csv");
			}
		}
	}
};
