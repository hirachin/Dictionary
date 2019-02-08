#pragma once
# include<Siv3D.hpp>
# include<HamFramework.hpp>

struct CommonData
{
	//String firstScene = L"DictionarySearch";
	String firstScene = L"AddWord";
};

using MyApp = SceneManager<String, CommonData>;

class Empty :public MyApp::Scene
{
public:

	void updateFadeIn(double)override
	{
		changeScene(m_data->firstScene, 0);
	}
};