﻿#pragma once
#include<map>
#include"Layer.h"
#include<d3dx9.h>
#include<string>
#include"ObjectLayer.h"
#include<rapidxml/rapidxml.hpp>
#include<rapidxml/rapidxml_utils.hpp>
using namespace rapidxml;


struct TileSet // dùng demo nữa ta mở rộng sau h chỉ đọc duy nhất 1 tileset
{
	int imageWidth;// chiều rộng hình  
	int imageHeight; //chiều dài hình 
	std::string name;
	int columns; // số cột được chia
	int rows; // số hàng được chia
	int tileCount;// tổng số tile được chia

	int tileWidth;
	int tileHeight;

};

enum class ObjLayer
{
	PlayerPos = 2,
	Ground = 3,
	Torch = 4,
	Camera = 5,
	HMoney = 14,
	Entrance = 8,
	CheckRetrograde = 18,
};

class Map
{
private:
	int width; 
	int height;

	int tileWidth;
	int tileHeight;
	TileSet tileSet;
	// lưu toàn bộ layer của map
	std::map<std::string, Layer*> layers;

	std::map<int, ObjectLayer*> objectLayers;
	void BuildMapLayer(xml_node<>* node);
	void BuildTileSet(xml_node<>* node);
	void BuildObjectLayer(xml_node<>* node);
public:


	std::map<int, ObjectLayer*> GetObjectLayer()
	{
		return objectLayers;

	}
	Map() :width(0), height(0), tileWidth(0), tileHeight(0) {};
	void BuildMap(const std::string path);

	void Render(D3DXVECTOR2 camera);
	Layer* GetLayer(std::string name);
};

