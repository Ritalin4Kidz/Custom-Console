#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"
#include <SYDEClickableButton.h>

class ShopItem
{
public:
	ShopItem() {}
	virtual ~ShopItem() {}

	CustomAsset getIcon() { return icon; }
	void setIcon(CustomAsset newIcon) { icon = newIcon; }

	int getPrice() { return price; }
	void setPrice(int newPrice) { price = newPrice; }

protected:
	CustomAsset icon;
	int price;
};

class MoveShopItem : public ShopItem
{
public:
	MoveShopItem() {}
	virtual ~MoveShopItem() { }
protected:
};


class ShopScene : public GameScene
{
public:
	ShopScene() { m_SceneTag = "Shop Scene"; m_isTransient = true;}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	void destroyScene() override;
private:
};