#pragma once
# include <Siv3D.hpp>

class Dictionary
{
	Array<std::pair<String, String>> m_datas;

	Array<FilePath> m_dictionaryPaths;

public:

	Dictionary() {}

	Dictionary(const FilePath& _path)
	{
		load(_path);
	}

	void add(const std::pair<String, String>& _data)
	{
		m_datas.push_back(_data);
	}

	void adds(const Array<std::pair<String, String>>& _datas)
	{
		for (auto&& d : _datas)
		{
			add(d);
		}
	}

	void reload()
	{
		m_datas.clear();
		const auto dictionaryPaths = m_dictionaryPaths;
		m_dictionaryPaths.clear();

		for (const auto& path : dictionaryPaths)
		{
			load(path);
		}

	}

	bool load(const FilePath& _path)
	{
		CSVReader reader(_path);

		if (!reader) { return false; }

		for (unsigned int i = 0; i < reader.rows; i++)
		{
			if (reader.columns(i) == 2)
			{
				m_datas.push_back(std::make_pair(reader.get<String>(i, 0), reader.get<String>(i, 1)));
			}
		}
		m_dictionaryPaths.push_back(_path);
		reader.close();
		return true;
	}

	bool save(const FilePath& _path)
	{
		CSVWriter writer(_path);

		if (!writer) { return false; }

		for (const auto& d : m_datas)
		{
			writer.writeRow(d.first, d.second);
		}

		writer.close();
		return true;
	}

	void sortEngliesh()
	{
		std::sort(m_datas.begin(), m_datas.end(), [](const std::pair<String, String>& a, const std::pair<String, String>& b)
		{
			return a.first < b.first;
		});
	}

	void sortJapanese()
	{
		std::sort(m_datas.begin(), m_datas.end(), [](const std::pair<String, String>& a, const std::pair<String, String>& b)
		{
			return a.second < b.second;
		});
	}

	void sortAndDeleteDuplication()
	{
		sortEngliesh();
		m_datas.erase(std::unique(m_datas.begin(), m_datas.end()), m_datas.end());
	}

	Array<std::pair<String, String>> getDatas()const
	{
		return m_datas;
	}

	Array<std::pair<String, String>> search(const String& _search)const
	{
		Array<std::pair<String, String>> findData;

		for (const auto& d : m_datas)
		{
			if (matchWord(_search, d.first))
			{
				findData.push_back(d);
			}
		}

		return findData;
	}

	bool matchWord(const String& _search, const String& _word)const
	{
		if (_search.length > _word.length) { return false; }

		for (unsigned int i = 0; i < _search.length; i++)
		{
			if (_search[i] != _word[i])
			{
				return false;
			}
		}

		return true;
	}
};