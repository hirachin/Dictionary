#pragma once
# include "SceneBase.h"
# include "Dictionary.h"
# include "InputWord.h"

class AddWord :public MyApp::Scene
{
	InputWord m_inputEnglish;
	InputWord m_inputJapanese;

	Table m_table;

	void init()override
	{
		m_inputEnglish = InputWord(L"wordFont", Size(300, 50));
		m_inputJapanese = InputWord(L"wordFont", Size(300, 50),false);
		m_table = Table();
	}

	void update()override
	{
		m_inputEnglish.update();
		m_inputJapanese.update();
	}

	void draw()const override
	{
		m_inputEnglish.draw(10, 20);
		m_inputJapanese.draw(Window::Width() / 2 + 10, 20);
	}
};