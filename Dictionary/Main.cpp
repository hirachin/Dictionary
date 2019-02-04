
# include <Siv3D.hpp>

# include "SceneBase.h"
# include "DictionarySearch.h"
# include "ScrollBar.h"

void Main()
{
	Graphics::SetBackground(Palette::White);
	Window::SetTitle(L"辞書");

	FontAsset::Register(L"wordFont", 20);
	FontAsset::Register(L"tableNumFont", 10);
	FontAsset::Register(L"tableFont", 15);

	MyApp manager;
	manager.add<Empty>(L"Empty");
	manager.add<DictionarySearch>(L"DictionarySearch");

	while (System::Update())
	{	
		manager.updateAndDraw();
	}
}
