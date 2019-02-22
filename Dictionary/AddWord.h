#pragma once
# include "SceneBase.h"
# include "Dictionary.h"
# include "InputWord.h"

class AddWord :public MyApp::Scene
{
	GUI m_gui;

	Table m_table;
	KeyMover m_keyMover;
	ScrollBar m_scrollBar;

	Array<std::pair<String, String>> m_inputDatas;

	PlusCombinedKeys m_addKey = PlusCombinedKeys(Input::KeyControl, Input::KeyEnter);
	PlusCombinedKeys m_saveKey = PlusCombinedKeys(Input::KeyControl, Input::KeyS);

	PlusCombinedKeys m_scrollRightKey = PlusCombinedKeys(Input::KeyControl, Input::KeyRight);
	PlusCombinedKeys m_scrollLeftKey = PlusCombinedKeys(Input::KeyControl, Input::KeyLeft);

	int m_cursor = 0;
	int m_initIdx = 0;


	bool save(const FilePath& _path)
	{
		Dictionary tempDictionary(_path);
		tempDictionary.adds(m_inputDatas);
		tempDictionary.sortAndDeleteDuplication();
		m_inputDatas.clear();
		return tempDictionary.save(_path);
	}

	bool addData()
	{
		if (m_gui.textField(L"english").text.isEmpty || m_gui.textField(L"japanese").text.isEmpty) { return false; }

		m_inputDatas.emplace_back(m_gui.textField(L"english").text, m_gui.textField(L"japanese").text);
		m_gui.textField(L"english").setText(L"");
		m_gui.textField(L"japanese").setText(L"");

		m_initIdx = 0;
		m_scrollBar.setRangeEnd(m_inputDatas.size() - 1);
		return true;
	}

	bool clickAddKey()const
	{
		return m_addKey.clicked || m_gui.button(L"add").pushed;
	}

	bool clickSaveKey()const
	{
		return m_saveKey.clicked || m_gui.button(L"save").pushed;
	}

	void scrollTable()
	{
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
	}

	void init()override
	{
		m_gui = GUI(GUIStyle::Default);
		m_gui.add(L"english", GUITextField::Create(10));
		m_gui.add(L"japanese", GUITextField::Create(10));
		m_gui.add(L"add", GUIButton::Create(L"’Ç‰Á"));
		m_gui.add(L"save", GUIButton::Create(L"•Û‘¶"));

		m_table = Table();
		m_keyMover = KeyMover(Input::KeyDown, Input::KeyUp);
		m_scrollBar = ScrollBar(0, 0, Point(610, 100), Size(20, 300));

	}

	void update()override
	{
		m_keyMover.update();
		m_scrollBar.update();

		scrollTable();

		if (clickAddKey())
		{
			addData();
		}

		if (clickSaveKey())
		{
			if (const auto savePath = Dialog::GetOpen({ ExtensionFilter::CSV }))
			{
				const FilePath path = savePath.value();
				save(path);
			}
		}

		if (m_scrollLeftKey.clicked || m_scrollRightKey.clicked)
		{
			changeScene(L"DictionarySearch");
			m_gui.hide();
		}

	}

	void draw()const override
	{
		Line(0, 90, Window::Width(), 90).draw(Palette::Black);
		m_table.draw(Point(10,100),m_inputDatas,m_initIdx);
		m_scrollBar.draw();
	}
};