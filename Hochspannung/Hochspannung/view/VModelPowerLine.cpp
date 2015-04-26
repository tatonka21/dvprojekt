#include "VModelPowerLine.h"

NAMESPACE_VIEW_B


#define SIZEOF_ARRAY(array) (sizeof(array) / sizeof(*array))

inline VModelPowerLine::DIRECTION operator|(VModelPowerLine::DIRECTION a, VModelPowerLine::DIRECTION b)
{
	return static_cast<VModelPowerLine::DIRECTION>(static_cast<int>(a) | static_cast<int>(b));
}

VModelPowerLine::VModelPowerLine(void) {

}

VModelPowerLine::VModelPowerLine(float fFieldSize) {
	m_fFieldSize = fFieldSize;
}

VModelPowerLine::~VModelPowerLine(void) {
	// TODO: add clean up for lines
}

void VModelPowerLine::SetPosition(int x, int y) {
	m_iGridPosition[0] = x;
	m_iGridPosition[1] = y;

	// translate
	m_zpMain.TranslateXDelta(CASTS<float>(x));
	m_zpMain.TranslateZDelta(CASTS<float>(y));
}

void VModelPowerLine::Init(DIRECTION eDirection, float fFoundationWidth, float fPylonHeight)
{
	m_zmGrey.MakeTextureDiffuse("textures\\texture_concrete_diffuse.png");
	m_zmGrey.MakeTextureBump("textures\\texture_concrete_normal.png");
	m_zmGrey.MakeTextureSpecular("textures\\texture_concrete_specular.png");
	m_zmBlack.MakeTextureDiffuse("textures\\black_image.jpg");

	// set necessary attributes depending on foundationWidth and pylonHeight
	m_fFoundationWidth		= m_fFieldSize * 0.3f;
	m_fFoundationHeight		= fFoundationWidth * 0.3f;
	m_fPylonHeight			= fPylonHeight;
	m_fPoleDistance			= fFoundationWidth * 0.8f;
	m_fPoleThickness		= m_fPoleDistance * 0.1f;
	m_fStrutHeight			= fPylonHeight * 0.1f;
	m_fStrutLength			= sqrtf(powf(m_fPoleDistance, 2) + powf(m_fStrutHeight, 2));
	m_fStrutAngle			= asinf(m_fStrutHeight / m_fStrutLength);;
	m_fStrutThickness		= m_fPoleDistance * 0.08f;
	m_iStrutsCount          = CASTS<int>(m_fPylonHeight / m_fStrutHeight);
	m_eDirection			= eDirection;
	
	m_fArmLength			= (m_fFieldSize - m_fPoleDistance) * 0.3f;
	m_fLowerArmPosition		= 2 * m_iArmPosition * m_fStrutHeight;
	m_fUpperArmPosition		= m_fLowerArmPosition + m_fStrutHeight * 2.0f;
	m_fUpperArmLength		= sqrt(pow(m_fStrutHeight, 2) + pow(m_fArmLength, 2));
	m_fArmAngle				= asinf(m_fStrutHeight / m_fUpperArmLength);

	m_fIsolatorLength    = m_fStrutHeight;
	m_fIsolatorThickness = m_fIsolatorLength * 0.1f;
	m_fRingRadius        = m_fIsolatorThickness;
	m_fRingThickness     = m_fIsolatorThickness * 0.25f;

	// init geometries (foundation, pole, strut)
	m_zgFoundation.Init(CHVector(m_fFoundationWidth, m_fFoundationHeight, m_fFoundationWidth), &m_zmGrey);
	m_zgPole.Init(CHVector(m_fPoleThickness, m_fPylonHeight, m_fPoleThickness), &m_zmBlack);
	m_zgStrut.Init(CHVector(m_fStrutLength, m_fStrutThickness, m_fStrutThickness), &m_zmBlack);
	m_zgRoof.Init(CHVector(m_fStrutThickness, m_fStrutLength, m_fStrutThickness), &m_zmBlack);
	m_zgSphere.Init(2 * m_fPoleThickness, &m_zmBlack);
	m_zgArm.Init(CHVector(m_fArmLength, m_fStrutThickness, m_fStrutThickness), &m_zmBlack);
	m_zgUpperArm.Init(CHVector(m_fUpperArmLength, m_fStrutThickness, m_fStrutThickness), &m_zmBlack);
	m_zgIsolatorLoD1.Init(m_fIsolatorThickness, m_fIsolatorThickness, m_fIsolatorLength, &m_zmBlack);
	m_zgIsolatorLoD2.Init(m_fIsolatorThickness, m_fIsolatorThickness, m_fIsolatorLength, &m_zmBlack, 6, false, false);
	m_zgIsolatorLoD3.Init(m_fIsolatorThickness, m_fIsolatorThickness, m_fIsolatorLength, &m_zmBlack, 4, false, false);
	m_zgRingLoD1.InitArc(m_fRingThickness, m_fRingThickness, m_fRingRadius, TWOPI, &m_zmBlack);
	m_zgRingLoD2.InitArc(m_fRingThickness, m_fRingThickness, m_fRingRadius, TWOPI, &m_zmBlack, 5, 5, false);
	m_zgRingLoD3.Init(CHVector(m_fRingRadius, m_fRingRadius, m_fRingRadius), &m_zmBlack);
	m_zgArmConnection.Init(CHVector(m_fStrutThickness, m_fStrutThickness, m_fPoleDistance), &m_zmBlack);
	m_zgLine.Init(m_fRingThickness, m_fRingThickness, m_fArmLength, &m_zmGrey, 4, false, false);

	// init ring vector
	for (int i = 0; i < 16; i++) {
		m_zpRing.push_back(*new CPlacement);
		m_zpRingLoD1.push_back(*new CPlacement);
		m_zpRingLoD2.push_back(*new CPlacement);
		m_zpRingLoD3.push_back(*new CPlacement);
		m_zpIsolator.push_back(*new CPlacement);
		m_zpIsolatorLoD1.push_back(*new CPlacement);
		m_zpIsolatorLoD2.push_back(*new CPlacement);
		m_zpIsolatorLoD3.push_back(*new CPlacement);
	}

	// preparing struts (rotate)
	m_zpStruts = new CPlacement[m_iStrutsCount * 8];
	for (int i = 0; i < m_iStrutsCount * 8; i++) {
		m_zpStruts[i].AddGeo(&m_zgStrut);
	}

	// preparing spheres
	for (int i = 0; i < 5; i++) {
		m_zpSphere[i].AddGeo(&m_zgSphere);
	}

	int index1, index2;
	float iYTranslation;
	std::bitset<4> direction = m_eDirection;
	// adding struts to poles
	for (int i = 0; i < 4; i++) {
		m_zpPole[i].AddGeo(&m_zgPole);
		m_zpRoof[i].AddGeo(&m_zgRoof);

		// adding struts
		for (int j = 0; j < m_iStrutsCount; j++) {
			index1 = (i * m_iStrutsCount * 2) + j;
			index2 = index1 + m_iStrutsCount;
			iYTranslation = j * m_fStrutHeight * 2 - m_fPylonHeight + m_fStrutHeight;

			m_zpPole[i].AddPlacement(&m_zpStruts[index1]);
			m_zpPole[i].AddPlacement(&m_zpStruts[index2]);

			m_zpStruts[index1].RotateZDelta(-m_fStrutAngle);
			m_zpStruts[index2].RotateZDelta(m_fStrutAngle);

			m_zpStruts[index1].TranslateDelta(m_fPoleDistance, iYTranslation, 0);
			m_zpStruts[index2].TranslateDelta(m_fPoleDistance, iYTranslation, 0);
		}
		m_zpPole[i].FixAndFasten();

		// adding roof
		m_zpRoof[i].RotateZDelta(-asinf((m_fPoleDistance + m_fPoleThickness) / (2 * (m_fStrutHeight - m_fStrutThickness))));
		m_zpRoof[i].RotateYDelta(AngleToRad(45));
		m_zpRoof[i].TranslateDelta(m_fPoleDistance * 0.5f, m_fPylonHeight + m_fStrutHeight * 1.1f, -4 * m_fPoleThickness);
		m_zpPole[i].AddPlacement(&m_zpRoof[i]);
		m_zpSphere[i].TranslateYDelta(m_fPylonHeight);
		m_zpPole[i].AddPlacement(&m_zpSphere[i]);

		// adding bottom arm poles
		m_zpLeftArmPole[i].AddGeo(&m_zgArm);
		m_zpLeftArmPole[i].TranslateDelta(-m_fArmLength - m_fPoleDistance, m_fLowerArmPosition, -m_fPoleDistance);
		m_zpArm[i].AddPlacement(&m_zpLeftArmPole[i]);

		m_zpRightArmPole[i].AddGeo(&m_zgArm);
		m_zpRightArmPole[i].TranslateDelta(-m_fArmLength - m_fPoleDistance, m_fLowerArmPosition, m_fPoleDistance);
		m_zpArm[i].AddPlacement(&m_zpRightArmPole[i]);

		// adding arm connection
		m_zpArmConnection.AddGeo(&m_zgArmConnection);
		m_zpArmConnection.Translate(-m_fArmLength + m_fStrutThickness * 2.0f, 0, m_fPoleDistance);
		m_zpLeftArmPole[i].AddPlacement(&m_zpArmConnection);

		// adding upper arm poles
		m_zpUpperLeftArmPole[i].RotateZDelta(m_fArmAngle);
		m_zpUpperLeftArmPole[i].AddGeo(&m_zgUpperArm);
		m_zpUpperLeftArmPole[i].TranslateDelta(-m_fArmLength - m_fPoleDistance, m_fUpperArmPosition, -m_fPoleDistance);
		m_zpUpperLeftArmPole[i].TranslateYDelta(-m_fStrutHeight);
		m_zpArm[i].AddPlacement(&m_zpUpperLeftArmPole[i]); 

		m_zpUpperRightArmPole[i].RotateZDelta(m_fArmAngle);
		m_zpUpperRightArmPole[i].AddGeo(&m_zgUpperArm);
		m_zpUpperRightArmPole[i].TranslateDelta(-m_fArmLength - m_fPoleDistance, m_fUpperArmPosition, m_fPoleDistance);
		m_zpUpperRightArmPole[i].TranslateYDelta(-m_fStrutHeight);
		m_zpArm[i].AddPlacement(&m_zpUpperRightArmPole[i]);

		// adding arms
		m_zpArm[i].RotateYDelta(i * HALFPI);
		m_zpFoundation.AddPlacement(&m_zpArm[i]);
		
		// adding isolators to arms
		m_zpTriangleIsolatorLoD1 = m_zgIsolatorLoD1.CopyToTriangleList();
		m_zpTriangleIsolatorLoD1->Subdivide(m_fIsolatorLength * 0.1f);
		m_zpTriangleIsolatorLoD1->WaveY(0.5f, 0.01f, 0);

		m_zpTriangleIsolatorLoD2 = m_zgIsolatorLoD2.CopyToTriangleList();
		m_zpTriangleIsolatorLoD2->Subdivide(m_fIsolatorLength * 0.2f);
		m_zpTriangleIsolatorLoD2->WaveY(0.5f, 0.01f, 0);

		m_zpTriangleIsolatorLoD3 = m_zgIsolatorLoD3.CopyToTriangleList();
		m_zpTriangleIsolatorLoD3->Subdivide(m_fIsolatorLength * 0.5f);
		m_zpTriangleIsolatorLoD3->WaveY(0.5f, 0.01f, 0);

		float dividedArm = m_fArmLength * 0.25f;

		m_zpIsolatorLoD1[i].SetLoD(0, 1.0f);
		m_zpIsolatorLoD2[i].SetLoD(1.0f, 3.0f);
		m_zpIsolatorLoD3[i].SetLoD(3.0f, 10.0f);
		m_zpRingLoD1[i].SetLoD(0, 0.5f);
		m_zpRingLoD2[i].SetLoD(0.5f, 3.0f);
		m_zpRingLoD3[i].SetLoD(3.0f, 10.0f);

		for (int j = 0; j < 4; j++)
		{
			m_zpIsolatorLoD1[i * 4 + j].AddGeo(m_zpTriangleIsolatorLoD1);
			m_zpIsolatorLoD2[i * 4 + j].AddGeo(m_zpTriangleIsolatorLoD2);
			m_zpIsolatorLoD3[i * 4 + j].AddGeo(m_zpTriangleIsolatorLoD3);

			m_zpIsolator[i * 4 + j].AddPlacement(&m_zpIsolatorLoD1[i]);
			m_zpIsolator[i * 4 + j].AddPlacement(&m_zpIsolatorLoD2[i]);
			m_zpIsolator[i * 4 + j].AddPlacement(&m_zpIsolatorLoD3[i]);

			// add isolators to the arm struts
			m_zpLeftArmPole[i].AddPlacement(&m_zpIsolator[i * 4 + j]);
			m_zpRightArmPole[i].AddPlacement(&m_zpIsolator[i * 4 + j]);
			m_zpIsolator[i * 4 + j].AddPlacement(&m_zpRing[i]);
		}

		m_zpIsolator[i * 4].Translate(dividedArm * -3.0f, -m_fIsolatorLength, 0);
		m_zpIsolator[i * 4 + 1].Translate(dividedArm * -2.0f, -m_fIsolatorLength, 0);
		m_zpIsolator[i * 4 + 2].Translate(dividedArm * 3.0f, -m_fIsolatorLength, 0);
		m_zpIsolator[i * 4 + 3].Translate(dividedArm * 2.0f, -m_fIsolatorLength, 0);
		
		m_zpIsolator[i].SetFrustumCullingOn();

		// add rings to connectors
		m_zpRingLoD1[i].AddGeo(&m_zgRingLoD1);
		m_zpRing[i].AddPlacement(&m_zpRingLoD1[i]);

		m_zpRingLoD2[i].AddGeo(&m_zgRingLoD2);
		m_zpRing[i].AddPlacement(&m_zpRingLoD2[i]);

		m_zpRingLoD3[i].AddGeo(&m_zgRingLoD3);
		m_zpRing[i].AddPlacement(&m_zpRingLoD3[i]);
		
		// rotate and translate rings
		m_zpRing[i].RotateXDelta(HALFPI);
		m_zpRing[i].RotateYDelta(HALFPI);
		m_zpRing[i].TranslateDelta(0, -m_fRingRadius, 0);
		m_zpRing[i].SetFrustumCullingOn();

		// switch on/off unnecessary arms and cables
		direction[i] ? m_zpArm[i].SwitchOn() : m_zpArm[i].SwitchOff();

		// rotate modeled pole and add it to foundation
		m_zpPole[i].RotateYDelta(i * HALFPI);
		m_zpFoundation.AddPlacement(&m_zpPole[i]);

	}

	// finally move the 4 poles into place
	m_zpPole[0].TranslateDelta(-m_fPoleDistance, m_fPylonHeight, m_fPoleDistance);
	m_zpPole[1].TranslateDelta(m_fPoleDistance, m_fPylonHeight, m_fPoleDistance);
	m_zpPole[2].TranslateDelta(m_fPoleDistance, m_fPylonHeight, -m_fPoleDistance);
	m_zpPole[3].TranslateDelta(-m_fPoleDistance, m_fPylonHeight, -m_fPoleDistance);

	m_zpFoundation.AddGeo(&m_zgFoundation);
	m_zpMain.AddPlacement(&m_zpFoundation);
}

VModelPowerLine::DIRECTION VModelPowerLine::Direction() {
	return m_eDirection;
}


//SHORT * VModelPowerLine::GridPosition() {
//	return m_iGridPosition;
//}

float VModelPowerLine::getWidth() {
	return m_fFoundationWidth;
}


float VModelPowerLine::getHeight()
{
	return m_fPylonHeight + m_fFoundationHeight;
}


NAMESPACE_VIEW_E
