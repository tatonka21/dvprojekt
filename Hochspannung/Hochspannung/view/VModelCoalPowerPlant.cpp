#include "VModelCoalPowerPlant.h"

NAMESPACE_VIEW_B


VModelCoalPowerPlant::VModelCoalPowerPlant()
{}

VModelCoalPowerPlant::~VModelCoalPowerPlant()
{}

void VModelCoalPowerPlant::init()
{
	m_zpLOD[0].AddPlacement(&m_zpKohlekraftwerk);
	m_zpLOD[1].AddPlacement(&m_zpKohlekraftwerk);
	m_zpLOD[2].AddPlacement(&m_zpKohlekraftwerk);

	//Initialisierung der Koerper
	m_zTrasse1.initViewModel(vBuilding);
	m_zTrasse2.initViewModel(vBuilding);
	m_zTrasse1.Init();
	m_zTrasse2.Init();

	//Gebirge
	m_zgBerg.Init(2.0f, 3.0f, &VMaterialLoader::m_zmKohleBerg, 16);

	//Schiene
	m_zgSchieneAussen.InitStraight(0.8f, 0.85f, 0.15f, &VMaterialLoader::m_zmAtomgrundGrey, 32, true);
	m_zgSchieneInnen.InitStraight(0.25f, 0.3f, 0.15f, &VMaterialLoader::m_zmAtomgrundGrey, 32, true);
	m_zgSprosse.Init(0.52f, 0.03f, 0.15f, &VMaterialLoader::m_zmHolz);

	//Initialisierung Fundament
	m_zgFoundation.Init(CHVector(5.0f, 0.3f, 5.0f), &VMaterialLoader::m_zmAtomgrundGreen);
	//m_zgFundament.Init(10.0f, 0.3f, 10.0f, &VMaterialLoader::m_zmAtomgrundGreen);

	//Mineneingang
	m_zgEingangOben.Init(1.2f, 0.15f, 2.0f, &VMaterialLoader::m_zmHolz);
	m_zgEingangSeite.Init(0.15f, 1.0f, 2.0f, &VMaterialLoader::m_zmHolz);
	m_zgMinenschacht.Init(1.1f, 1.0f, 0.1f, &VMaterialLoader::m_zmKohleBlack);

	//Minenlore
	m_zgLoreRad.Init(0.08f, 0.08f, 0.04f, &VMaterialLoader::m_zmAtomgrundGrey);
	m_zgLoreVorne.Init(0.5f, 0.5f, 0.05f, &VMaterialLoader::m_zmKohleLore);
	m_zgLoreSeite.Init(0.05f, 0.5f, 0.5f, &VMaterialLoader::m_zmKohleLore);
	m_zgLoreBoden.Init(0.45f, 0.05f, 0.48f, &VMaterialLoader::m_zmKohle);

	//Kamin
	m_zgKamin.InitStraight(0.2f, 0.3f, 3.0f, &VMaterialLoader::m_zmAtomgrundGrey, 32, true);


	//Placements


	m_zpKohlekraftwerk.AddPlacement(m_zTrasse1.getMainPlacement());
	m_zpKohlekraftwerk.AddPlacement(m_zTrasse2.getMainPlacement());
	m_zpKohlekraftwerk.AddPlacement(&m_zpFundament);
	m_zpKohlekraftwerk.AddPlacement(&m_zpGebirge);
	m_zpKohlekraftwerk.AddPlacement(&m_zpGleiswerk);
	m_zpGleiswerk.AddPlacement(&m_zpGleis);
	m_zpKohlekraftwerk.AddPlacement(&m_zpMineneingang);
	m_zpGleiswerk.AddPlacement(&m_zpMinenLore);
	//m_zpKohlekraftwerk.AddPlacement(&m_zpGebaeude);

	//m_zpGebaeude.AddPlacement(Gebaeude);
	//m_zpGebaeude.AddPlacement(&m_zpKamin1);
	//m_zpGebaeude.AddPlacement(&m_zpKamin2);
	//m_zpGebaeude.AddPlacement(&m_zpKamin3);

	m_zpGebirge.AddPlacement(&m_zpBerg1);
	m_zpGebirge.AddPlacement(&m_zpBerg2);
	m_zpGebirge.AddPlacement(&m_zpBerg3);
	m_zpGebirge.AddPlacement(&m_zpBerg4);
	m_zpGebirge.AddPlacement(&m_zpBerg5);
	m_zpGebirge.AddPlacement(&m_zpBerg6);
	m_zpGebirge.AddPlacement(&m_zpBerg7);
	m_zpGebirge.AddPlacement(&m_zpBerg8);

	//Gleis
	m_zpGleis.AddPlacement(&m_zpSchieneAussen);
	m_zpGleis.AddPlacement(&m_zpSchieneInnen);
	for (int i = 0; i < 8; i++)
	{
		m_zpGleis.AddPlacement(&m_zpSprossen[i]);
	}
	//Mineneingang
	m_zpMineneingang.AddPlacement(&m_zpEingangOben);
	m_zpMineneingang.AddPlacement(&m_zpEingangRechts);
	m_zpMineneingang.AddPlacement(&m_zpEingangLinks);
	m_zpMineneingang.AddPlacement(&m_zpMinenschacht);

	//Lore
	m_zpMinenLore.AddPlacement(&m_zpWandHinten);
	m_zpMinenLore.AddPlacement(&m_zpWandVorne);
	m_zpMinenLore.AddPlacement(&m_zpWandRechts);
	m_zpMinenLore.AddPlacement(&m_zpWandLinks);
	m_zpMinenLore.AddPlacement(&m_zpBoden);
	m_zpMinenLore.AddPlacement(&m_zpRadHintenLinks);
	m_zpMinenLore.AddPlacement(&m_zpRadHintenRechts);
	m_zpMinenLore.AddPlacement(&m_zpRadVorneLinks);
	m_zpMinenLore.AddPlacement(&m_zpRadVorneRechts);




	//Adding

	//m_zpFundament.Translate(CHVector(-5.0f, 0.0f, -5.0f));
	m_zpFundament.AddGeo(&m_zgFoundation);

	m_zpBerg1.AddGeo(&m_zgBerg);

	m_zpBerg2.Scale(0.9f);
	m_zpBerg2.TranslateDelta(CHVector(0.5f, 0.0f, 0.0f));
	m_zpBerg2.AddGeo(&m_zgBerg);

	m_zpBerg3.Scale(0.8f);
	m_zpBerg3.TranslateDelta(CHVector(-1.0f, 0.0f, 0.5f));
	m_zpBerg3.AddGeo(&m_zgBerg);

	m_zpBerg4.Scale(0.6f);
	m_zpBerg4.TranslateDelta(CHVector(1.5f, 0.0f, 0.5f));
	m_zpBerg4.AddGeo(&m_zgBerg);

	m_zpBerg5.Scale(0.9f);
	m_zpBerg5.TranslateDelta(CHVector(2.0f, 0.0f, -0.5f));
	m_zpBerg5.AddGeo(&m_zgBerg);

	m_zpBerg6.Scale(0.85f);
	m_zpBerg6.TranslateDelta(CHVector(-2.0f, 0.0f, -0.5f));
	m_zpBerg6.AddGeo(&m_zgBerg);

	m_zpBerg7.Scale(0.7f);
	m_zpBerg7.TranslateDelta(CHVector(-2.0f, 0.0f, 0.5f));
	m_zpBerg7.AddGeo(&m_zgBerg);

	m_zpBerg8.Scale(0.7f);
	m_zpBerg8.TranslateDelta(CHVector(2.5f, 0.0f, 0.6f));
	m_zpBerg8.AddGeo(&m_zgBerg);

	m_zpGebirge.Scale(1.2f);
	m_zpGebirge.ScaleXDelta(1.1f);
	m_zpGebirge.TranslateDelta(CHVector(-0.2f, 0.2f, -2.3f));

	//Gleis
	m_zpSchieneAussen.Translate(CHVector(0.0f, 0.3f, 0.0f));
	m_zpSchieneAussen.AddGeo(&m_zgSchieneAussen);

	m_zpSchieneInnen.Translate(CHVector(0.0f, 0.3f, 0.0f));
	m_zpSchieneInnen.AddGeo(&m_zgSchieneInnen);

	//Trassen
	m_zTrasse1.getMainPlacement()->Translate(CHVector(-3.0f, 0.35f, 4.0f));
	m_zTrasse2.getMainPlacement()->Translate(3.0f, 0.35f, 4.0f);

	//Sprossen-Array
	for (int i = 0; i < 8; i++)
	{
		m_zpSprossen[i].Translate(CHVector(0.27f, 0.3f, 0.0f));
		m_zpSprossen[i].RotateYDelta(((2 * PI) / 8) * i);
		m_zpSprossen[i].AddGeo(&m_zgSprosse);
	}

	//Mineneingang
	m_zpEingangOben.Translate(CHVector(-2.35f, 1.3f, -1.0f));
	m_zpEingangOben.AddGeo(&m_zgEingangOben);

	m_zpEingangRechts.Translate(CHVector(-1.3f, 0.3f, -1.0f));
	m_zpEingangRechts.AddGeo(&m_zgEingangSeite);

	m_zpEingangLinks.Translate(CHVector(-2.35f, 0.3f, -1.0f));
	m_zpEingangLinks.AddGeo(&m_zgEingangSeite);

	m_zpMinenschacht.Translate(CHVector(-2.3f, 0.3f, 0.1f));
	m_zpMinenschacht.AddGeo(&m_zgMinenschacht);

	//Minenlore
	m_zpWandVorne.Translate(CHVector(0.0f, 0.4f, 0.5f));
	m_zpWandVorne.AddGeo(&m_zgLoreVorne);

	m_zpWandHinten.Translate(CHVector(0.0f, 0.4f, 0.0f));
	m_zpWandHinten.AddGeo(&m_zgLoreVorne);

	m_zpWandLinks.Translate(CHVector(0.0f, 0.4f, 0.0f));
	m_zpWandLinks.AddGeo(&m_zgLoreSeite);

	m_zpWandRechts.Translate(CHVector(0.45f, 0.4f, 0.0f));
	m_zpWandRechts.AddGeo(&m_zgLoreSeite);

	m_zpBoden.Translate(CHVector(0.0001f, 0.75f, 0.02f));
	m_zpBoden.AddGeo(&m_zgLoreBoden);


	m_zpRadHintenLinks.RotateZ(HALFPI);
	m_zpRadHintenLinks.TranslateDelta(CHVector(0.025f, 0.4f, 0.1f));
	m_zpRadHintenLinks.AddGeo(&m_zgLoreRad);

	m_zpRadHintenRechts.RotateZ(HALFPI);
	m_zpRadHintenRechts.TranslateDelta(CHVector(0.525f, 0.4f, 0.1f));
	m_zpRadHintenRechts.AddGeo(&m_zgLoreRad);

	m_zpRadVorneRechts.RotateZ(HALFPI);
	m_zpRadVorneRechts.TranslateDelta(CHVector(0.025f, 0.4f, 0.45f));
	m_zpRadVorneRechts.AddGeo(&m_zgLoreRad);

	m_zpRadVorneLinks.RotateZ(HALFPI);
	m_zpRadVorneLinks.TranslateDelta(CHVector(0.525f, 0.4f, 0.45f));
	m_zpRadVorneLinks.AddGeo(&m_zgLoreRad);

	m_zpMinenLore.Translate(CHVector(-1.98f, 0.025f, -1.0f));
	
	//m_zpMinenLore.Translate(CHVector(0.25f, 0.0f, -0.3f));
	m_zpGleiswerk.Translate(CHVector(-1.7f, 0.0f, 2.5f));

	//Gebaeude->ScaleZDelta(3.0f);
	m_zpKamin1.Translate(CHVector(0.75f, 1.5f, 0.8f));
	m_zpKamin1.AddGeo(&m_zgKamin);
	m_zpKamin2.Translate(CHVector(1.75f, 1.5f, 0.8f));
	m_zpKamin2.AddGeo(&m_zgKamin);
	m_zpKamin3.Translate(CHVector(2.75f, 1.5f, 0.8f));
	m_zpKamin3.AddGeo(&m_zgKamin);


	//m_zpGebaeude.Translate(CHVector(0.3f, 0.3f, 1.0f));
}

void VModelCoalPowerPlant::moveLore(float amount, float fTime)
{
	//m_zpMinenLore.TranslateZDelta(0.1*sin(fTime));

	if (totalMovement <= 3.0f)
	{
		m_zpMinenLore.TranslateZDelta(amount);
	}
	else if (totalMovement > 3.0f && totalMovement <= 6.0f)
	{
		m_zpMinenLore.TranslateZDelta(-amount);
	}
	else
	{
		totalMovement = 0.0f;
	}

	totalMovement += amount;
}

NAMESPACE_VIEW_E
