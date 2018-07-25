#pragma once
#include "GameUnit.h"

class GamePlayer : public GameUnit
{
public:
	enum class LowerAction;
	enum class UpperAction;

public:
	GamePlayer(wstring animPath, wstring matFile, wstring meshFile);
	~GamePlayer();

	void Update();
	void Render();

private:
	void HandleInput();

	void LoadAnimation(wstring path);

	void PlayLowerAction(LowerAction action);
	void PlayLowerAction(LowerAction action, float startTime);

	void PlayUpperAction(UpperAction action);
	void PlayUpperAction(UpperAction action, float startTime);

	void ActionMovement(D3DXVECTOR3 direction);

private:
	struct GamePlayerSpec* specData;
	struct GamePlayerInput* input;

	bool bRunning;

	D3DXVECTOR3 moveDirection;
	float moveElapsedTime;
	
	float actionElapsedTime;

	float rootRotationAngle;
	float rootElapsedAngle;

	bool bActiveBooster;
	

	float runDurationTime;
	float walkDurationTime;
	float boosterFinishDurationTime;
	float boosterBreakDurationTime;
	float weaponChangeDurationTime;

private:
	enum class DebugMode
	{
		None = 0, NeverDie, Superman, God,
	};
	DebugMode debugMode;


	enum class LowerAction
	{
		Unknown = 0,
		Idle, Run, Damage, Walk, BackWalk, LeftTurn, RightTurn,
		ForwardDead, BackwardDead, LeftDead, RightDead,
		BoosterPrepare, BoosterActive, BoosterFinish, BoosterBreak,
		BoosterLeftTurn, BoosterRightTurn,
		Count,
	};

	enum class UpperAction
	{
		Unknown = 0,
		Idle, Run, Damage, WeaponChange,
		ForwardNonFire, LeftNonFire, RightNonFire,
		ForwardMachineGunFire, LeftMachineGunFire, RightMachineGunFire, ReloadMachineGun,
		ForwardShotgunFire, LeftShotgunFire, RightShotgunFire, ReloadShotgun,
		ForwardHandgunFire, LeftHandgunFire, RightHandgunFire, ReloadHandgun,
		ForwardDead, BackwardDead, LeftDead, RightDead,
		BoosterPrepare, BoosterActive, BoosterFinish, BoosterBreak,
		BoosterLeftTurn, BoosterRightTurn,
		Count,
	};

private:
	LowerAction currentLowerAction;
	UpperAction currentUpperAction;

	LowerAction prepareLowerAction;
	UpperAction prepareUpperAction;

	bool bOverwriteLowerAction;
	bool bOverwriteUpperAction;

	vector<UINT> indexLowerAnimations;
	vector<UINT> indexUpperAnimations;
};