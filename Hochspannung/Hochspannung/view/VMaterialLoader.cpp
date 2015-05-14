#include "VMaterialLoader.h"

NAMESPACE_VIEW_B


std::map<VMaterialLoader::FieldPair, CMaterial> VMaterialLoader::fieldMaterials;

//MainMenue
CMaterial VMaterialLoader::materialMainMenueBackground;

CMaterial VMaterialLoader::materialCoalPowerPlant;
CMaterial VMaterialLoader::materialHydroelectricPowerPlant;
CMaterial VMaterialLoader::materialMainMenue;
CMaterial VMaterialLoader::materialMainMenueHover;
CMaterial VMaterialLoader::materialIngameCraft;
CMaterial VMaterialLoader::materialDialogBackground;
CMaterial VMaterialLoader::materialIngameBorder;
CMaterial VMaterialLoader::materialTopbar;

CMaterial VMaterialLoader::materialRed;
CMaterial VMaterialLoader::materialBlue;
CMaterial VMaterialLoader::materialGreen;

//Infofield
CMaterial VMaterialLoader::materialInfofieldBackground;

//Minimap
CMaterial VMaterialLoader::materialMinimapBackground;

//Lobby Buttons

CMaterial VMaterialLoader::materialButtonLobbyJoinGame;
CMaterial VMaterialLoader::materialButtonLobbyJoinGameHover;
CMaterial VMaterialLoader::materialButtonLobbyHostGame;
CMaterial VMaterialLoader::materialButtonLobbyHostGameHover;



//Buttons

CMaterial VMaterialLoader::materialButtonMainMenueNeuesSpiel;
CMaterial VMaterialLoader::materialButtonMainMenueNeuesSpielHover;
CMaterial VMaterialLoader::materialButtonMainMenueOptionen;
CMaterial VMaterialLoader::materialButtonMainMenueOptionenHover;
CMaterial VMaterialLoader::materialButtonMainMenueCredits;
CMaterial VMaterialLoader::materialButtonMainMenueCreditsHover;
CMaterial VMaterialLoader::materialButtonMainMenueSpielBeenden; 
CMaterial VMaterialLoader::materialButtonMainMenueSpielBeendenHover;


CMaterial VMaterialLoader::materialButtonBack;
CMaterial VMaterialLoader::materialButtonBackHover;
CMaterial VMaterialLoader::materialBottombarBorderTop;
CMaterial VMaterialLoader::materialVerticalBorder;
CMaterial VMaterialLoader::materialLobbyBigDialog;
CMaterial VMaterialLoader::materialBuildingButton;
CMaterial VMaterialLoader::materialBuildingButtonHover;

CMaterial VMaterialLoader::materialButtonAbort;
CMaterial VMaterialLoader::materialButtonAbortHover;

//Ingame Buttons
CMaterial VMaterialLoader::materialIngameButtonCraftmenu;
CMaterial VMaterialLoader::materialIngameButtonSabotage;
CMaterial VMaterialLoader::materialIngameButtonStatistics;

CMaterial VMaterialLoader::materialIngameButtonCraftmenuHover;
CMaterial VMaterialLoader::materialIngameButtonSabotageHover;
CMaterial VMaterialLoader::materialIngameButtonStatisticsHover;
//Craftmenu
CMaterial VMaterialLoader::materialCraftmenuButtonWindmill;
CMaterial VMaterialLoader::materialCraftmenuButtonHydroPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonSolarPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonCoalPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonOilPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonNuclearPowerplant;
CMaterial VMaterialLoader::materialCraftmenuButtonPowerline;

CMaterial VMaterialLoader::materialCraftmenuButtonWindmillHover;
CMaterial VMaterialLoader::materialCraftmenuButtonHydroPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonSolarPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonCoalPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonOilPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonNuclearPowerplantHover;
CMaterial VMaterialLoader::materialCraftmenuButtonPowerlineHover;

//WritingFont
CWritingFont VMaterialLoader::standardFont;
CWritingFont VMaterialLoader::GoldFont;

//Trassentexturen
CMaterial VMaterialLoader::m_zmConcrete;
CMaterial VMaterialLoader::m_zmStrut;
CMaterial VMaterialLoader::m_zmIsolator;
CMaterial VMaterialLoader::m_zmRing;
CMaterial VMaterialLoader::m_zmCable;

//Solarkraftwerktexturen
CMaterial VMaterialLoader::m_zmSolarzelle;
CMaterial VMaterialLoader::m_zmSolarGrund;
CMaterial VMaterialLoader::m_zmSolarLOD;

//Atomkraftwerktexturen
CMaterial VMaterialLoader::m_zmAtomgrundWhite;
CMaterial VMaterialLoader::m_zmAtomgrundGrey;
CMaterial VMaterialLoader::m_zmSchranke;
CMaterial VMaterialLoader::m_zmAtomgrundGreen;
CMaterial VMaterialLoader::m_zmHolz;

//PlayerColor
std::unordered_map<int, CColor> VMaterialLoader::colorPlayers;

//PlayerFoundations
std::unordered_map<int, CMaterial> VMaterialLoader::materialFoundationPlayer;

//Cursor
CMaterial VMaterialLoader::m_zmDefaultCursor;
CMaterial VMaterialLoader::m_zmHammerCursor;

//CraftMenue
CMaterial VMaterialLoader::m_zmCraftMenueBackground;

//MaterialBuilding
CMaterial VMaterialLoader::materialBuilding01;
CMaterial VMaterialLoader::materialBuilding02;
CMaterial VMaterialLoader::materialBuilding03;
CMaterial VMaterialLoader::materialLargeOfficeBuilding;
CMaterial VMaterialLoader::materialAppartments;
CMaterial VMaterialLoader::materialOfficTowerViewingDeck;
CMaterial VMaterialLoader::materialTwistedTower;
CMaterial VMaterialLoader::materialSmallOfficeBuilding;

// MaterialWindowBuildings
CMaterial VMaterialLoader::materialWindowsofBuilding;

void VMaterialLoader::setFieldMaterialHelper(const LField::FieldType fieldType, const std::string& textureName)
{
	std::string textureDiffuse = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_diffuse.png");
	std::string textureSpecular = std::string("textures/terrain/texture_terrain_") + textureName + std::string("_specular.png");
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureDiffuse(const_cast<char*>(textureDiffuse.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL1)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL2)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
	fieldMaterials[FieldPair(fieldType, LField::LEVEL3)].MakeTextureSpecular(const_cast<char*>(textureSpecular.c_str()));
}

void VMaterialLoader::init()
{
	setFieldMaterialHelper(LField::WATER, "water");
	setFieldMaterialHelper(LField::AIR, "air");
	setFieldMaterialHelper(LField::SOLAR, "solar");
	setFieldMaterialHelper(LField::COAL, "coal");
	setFieldMaterialHelper(LField::GRASS, "base");
	setFieldMaterialHelper(LField::MOUNTAIN, "mountain");
	setFieldMaterialHelper(LField::CITY, "city");
	setFieldMaterialHelper(LField::OIL, "oil");
	setFieldMaterialHelper(LField::NUCLEAR, "atom");

	materialCoalPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");
	materialHydroelectricPowerPlant.MakeTextureDiffuse("textures\\_original.jpg");

	materialDialogBackground.MakeTextureSprite("textures\\MainMenueBackground.png");

	materialIngameBorder.Init(CColor(0.0, 0.44, 0.68), CColor(0.0, 0.44, 0.68), CColor(0.0, 0.44, 0.68));


	//Main menu - Buttons
	materialButtonMainMenueNeuesSpiel.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_newgame.png");
	materialButtonMainMenueNeuesSpielHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_newgame_hover.png");
	materialButtonMainMenueOptionen.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_options.png");
	materialButtonMainMenueOptionenHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_options_hover.png");
	materialButtonMainMenueCredits.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_credits.png");
	materialButtonMainMenueCreditsHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_credits_hover.png");
	materialButtonMainMenueSpielBeenden.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_exit.png");
	materialButtonMainMenueSpielBeendenHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_exit_hover.png");
	materialButtonBack.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_back.png");
	materialButtonBackHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_back_hover.png");
	materialButtonAbort.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_abort.png");
	materialButtonAbortHover.MakeTextureSprite("textures/gui/menu/texture_gui_menubutton_abort_hover.png");

	//MainMenue Background
	materialMainMenueBackground.MakeTextureSprite("textures/gui/background/wasserkraftwerk.png");

	//Lobby Buttons
	materialButtonLobbyJoinGame.MakeTextureSprite("textures/gui/Buttons/ButtonJoinGame.png");
	materialButtonLobbyJoinGameHover.MakeTextureSprite("textures/gui/Buttons/ButtonJoinGameHover.png");
	materialButtonLobbyHostGame.MakeTextureSprite("textures/gui/Buttons/ButtonHostGame.png");
	materialButtonLobbyHostGameHover.MakeTextureSprite("textures/gui/Buttons/ButtonHostGameHover.png");
		

	//Interface - Background
	materialTopbar.MakeTextureSprite("textures\\topbar.png");
	materialBottombarBorderTop.MakeTextureSprite("textures\\bottombarBorderTopBlue.png");
	materialVerticalBorder.MakeTextureSprite("textures\\VerticalBorder.png");
	materialLobbyBigDialog.MakeTextureSprite("textures\\LobbyBigDialog.png");
	materialBuildingButton.MakeTextureSprite("textures\\BuildingButton.png");
	materialBuildingButtonHover.MakeTextureSprite("textures\\BuildingButtonHover.png");

	//Interface - Selection Buttons
	materialIngameButtonCraftmenu.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu.png");
	materialIngameButtonCraftmenuHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_craftmenu_hover.png");
	materialIngameButtonSabotage.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage.png");
	materialIngameButtonSabotageHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_sabotage_hover.png");
	materialIngameButtonStatistics.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics.png");
	materialIngameButtonStatisticsHover.MakeTextureSprite("textures/gui/interface/texture_gui_ingamebutton_statistics_hover.png");

	//Interface - Panel_Building
	materialCraftmenuButtonWindmill.MakeTextureSprite("textures/gui/Buttons/gui_ingame_airPowerPlant.png");
	materialCraftmenuButtonHydroPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_hydroPowerPlant.png");
	materialCraftmenuButtonSolarPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_solarPowerPlant.png");
	materialCraftmenuButtonCoalPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_coalPowerPlant.png");
	materialCraftmenuButtonOilPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_oilPowerPlant.png");
	materialCraftmenuButtonNuclearPowerplant.MakeTextureSprite("textures/gui/Buttons/gui_ingame_nuclearPowerPlant.png");
	materialCraftmenuButtonPowerline.MakeTextureSprite("textures/gui/Buttons/gui_ingame_powerLine.png");

	materialCraftmenuButtonWindmillHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_airPowerPlantHover.png");
	materialCraftmenuButtonHydroPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_hydroPowerPlantHover.png");
	materialCraftmenuButtonSolarPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_solarPowerPlantHover.png");
	materialCraftmenuButtonCoalPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_coalPowerPlantHover.png");
	materialCraftmenuButtonOilPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_oilPowerPlantHover.png");
	materialCraftmenuButtonNuclearPowerplantHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_nuclearPowerPlantHover.png");
	materialCraftmenuButtonPowerlineHover.MakeTextureSprite("textures/gui/Buttons/gui_ingame_powerLineHover.png");

	//Test
	materialRed.MakeTextureSprite("textures\\red_image.jpg");
	materialBlue.MakeTextureSprite("textures\\blue_image.jpg");
	materialGreen.MakeTextureSprite("textures\\green_image.jpg");

	//Fonts
	standardFont.Init("textures/fonts/FontArialShadow.png", true);
	standardFont.SetTableSize(16, 16);
	GoldFont.Init("textures/fonts/FontArialShadowGold.png", true);
	GoldFont.SetTableSize(16, 6);
	standardFont.SetTransparencyOn();
	//Building - Trasse
	m_zmConcrete.MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse.png");
	m_zmConcrete.MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	m_zmConcrete.MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");

	m_zmStrut.MakeTextureDiffuse("textures/buildings/strommast_diffuse.png");
	m_zmIsolator.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmRing.MakeTextureDiffuse("textures\\black_image.jpg");
	m_zmCable.MakeTextureDiffuse("textures\\white_image.jpg");

	//Solarkraftwerktexturen
	m_zmSolarGrund.MakeTextureDiffuse("textures\\white_image.jpg");
	m_zmSolarzelle.MakeTextureDiffuse("textures\\buildings\\SolarPanel_diffuse.jpg");
	m_zmSolarzelle.MakeTextureBump("textures\\buildings\\SolarPanel_bump.jpg");
	m_zmSolarLOD.MakeTextureDiffuse("textures\\SolarLOD.jpg");

	//Atomkraftwerktexturen
	m_zmAtomgrundWhite.MakeTextureDiffuse("textures\\white_image.jpg");
	m_zmAtomgrundGrey.MakeTextureDiffuse("Textures\\grey_image.jpg");
	m_zmSchranke.MakeTextureDiffuse("Textures\\schranke.jpg");
	m_zmAtomgrundGreen.MakeTextureDiffuse("Textures\\green_image.jpg");
	m_zmHolz.MakeTextureDiffuse("Textures\\Holz.JPG");
	
	//Building - Foundation
	colorPlayers.emplace(std::piecewise_construct, std::make_tuple(LPlayer::External), std::make_tuple(196.0f / 255.0f, 51.0f / 255.0f, 66.0f / 255.0f));
	colorPlayers.emplace(std::piecewise_construct, std::make_tuple(LPlayer::Local), std::make_tuple(222.0f / 255.0f, 186.0f / 255.0f, 69.0f / 255.0f));
	//Local player
	materialFoundationPlayer[LPlayer::Local].MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse_player_local.png");
	materialFoundationPlayer[LPlayer::Local].MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	materialFoundationPlayer[LPlayer::Local].MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");
	//Opponent
	materialFoundationPlayer[LPlayer::External].MakeTextureDiffuse("textures/buildings/texture_concrete_diffuse_player_opponent.png");
	materialFoundationPlayer[LPlayer::External].MakeTextureBump("textures/buildings/texture_concrete_normal.png");
	materialFoundationPlayer[LPlayer::External].MakeTextureSpecular("textures/buildings/texture_concrete_specular.png");

	//Cursor
	m_zmDefaultCursor.MakeTextureSprite("textures\\gui\\default_zeiger.png");
	m_zmHammerCursor.MakeTextureSprite("textures\\gui\\Hammer.png");

	//CraftMenue
	m_zmCraftMenueBackground.MakeTextureSprite("textures/gui/background/gui_ingame_baumenu.png");

	//Infofield
	materialInfofieldBackground.MakeTextureSprite("textures/gui/background/gui_ingame_infofield.png");

	//Minimap
	materialMinimapBackground.MakeTextureSprite("textures/gui/background/gui_ingame_minimap.png");
}


NAMESPACE_VIEW_E
