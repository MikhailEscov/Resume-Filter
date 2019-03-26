//---------------------------------------------------------------------------
#include "Unit1.h"
#ifndef FilterClassesH
#define FilterClassesH
//---------------------------------------------------------------------------
class GasClass{
protected:
	bool IsAuto;
	float T,P,F;
	float Tsim,Fzd,Fmax,Pmax;
	int Klapan;
	void Simulation();

public:
	GasClass();
	~GasClass();
	void OneMoreMoment();

	float GetT();
	float GetP();
	float GetF();
	int GetKlapan();
	void SetFzd(float newFzd);
	void SetKlapan(int newKlapan);
	void SetAutoMode(bool newIsAuto);
	void SetTsim(float newTsim);
	void SetFPmax(float newFmax,float newPmax);
};
//---------------------------------------------------------------------------
class ImpulseGasClass:public GasClass{
protected:
	float Pzd;
	float Perepadzd;
	double TimeImpulseDuration;
	double TimeImpulseStart;
	double TimeImpulsePeriodDuration;
	double TimeImpulsePeriodStart;
public:
	ImpulseGasClass();
	~ImpulseGasClass();
	void OneMoreMoment(float PerepadNow);
	void Impulse();
	void SetPzd(float newPzd);
	void SetPerepadzd(float newPerepadzd);
	void SetTimeImpulseDuration(double newTimeImpulseDuration);
	void SetTimeImpulsePeriodDuration(double newTimeImpulsePeriodDuration);

};
//---------------------------------------------------------------------------
class SmokePlusVozduhGasClass:public GasClass{
protected:
	float Tzd;
public:
	SmokePlusVozduhGasClass();
	~SmokePlusVozduhGasClass();
	void SetTzd(float newTzd);
	float GetTzd();
};
//---------------------------------------------------------------------------
class ContainerClass{
protected:
	bool IsAuto;
	bool IsOn;//выбрасывает ли мусор
	float Level, Levelzd;//0-3
public:
	TLabel *LabelTrash;
	ContainerClass();
	~ContainerClass();
	void OneMoreMoment(int addToLevel);
	float GetLevel();
	void SetLevelzd(float newLevelzd);
	void SetIsAuto(bool newIsAuto);
	void SetIsOn(bool newIsOn);
};
//---------------------------------------------------------------------------
class PieceOfDirtClass{
protected:
	bool Fly;
	int StartTop,StartLeft;
    int Power;
	int MoveAddTop,MoveAddLeft;
	int MoveLeftTop,MoveLeftLeft;
public:
	int Top,Left;
	TColor Color;
	PieceOfDirtClass(int newStartLeft,int newStartTop,int newMoveAddLeft,int newMoveAddTop);
	~PieceOfDirtClass();
	int OneMoreMoment(int Dirty, int ContainerTop);
	void StartToFly();
};
//---------------------------------------------------------------------------
class FilterClass{
protected:
	 float Pin,Pout;
	 int Dirty;//max 255
	 bool IsFly;
public:
	ContainerClass *Container;
	PieceOfDirtClass *PieceOfDirt[3][160*2+23];

	FilterClass();
	~FilterClass();
	int OneMoreMoment(int intensity);
	void Impulse();
	float GetPerepad();
};
//---------------------------------------------------------------------------
#endif
