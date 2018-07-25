#include "stdafx.h"
#include "GamePlayer.h"
#include "GameData.h"
#include "GamePlayerInput.h"

GamePlayer::GamePlayer(wstring animPath, wstring matFile, wstring meshFile)
	: GameUnit(matFile, meshFile)
{
	specData = new GamePlayerSpec();
	input = new GamePlayerInput();

	bRunning = true;
	
	moveDirection = D3DXVECTOR3(0, 0, 0);
	moveElapsedTime = 0.0f;
	actionElapsedTime = 0.0f;

	rootRotationAngle = 0;
	rootElapsedAngle = 0;

	bActiveBooster = false;

	bOverwriteLowerAction = false;
	bOverwriteUpperAction = false;

	prepareLowerAction = LowerAction::Unknown;
	prepareUpperAction = UpperAction::Unknown;



	LoadAnimation(animPath);

	PlayLowerAction(LowerAction::Idle);
	PlayUpperAction(UpperAction::Idle);
}

GamePlayer::~GamePlayer()
{
	SAFE_DELETE(specData);
	SAFE_DELETE(input);
}

void GamePlayer::Update()
{
	HandleInput();

	if (prepareLowerAction != LowerAction::Unknown || bOverwriteLowerAction == true)
		PlayLowerAction(prepareLowerAction);

	if (prepareUpperAction != UpperAction::Unknown || bOverwriteLowerAction == true)
		PlayUpperAction(prepareUpperAction);

	GameUnit::Update();
}

void GamePlayer::Render()
{
	GameUnit::Render();
}

void GamePlayer::HandleInput()
{
	bool bGoing = false;
	D3DXVECTOR3 velocity(0, 0, 0);

	
	//////////////////////////////////////////////////////////
	// ÀÌµ¿
	//////////////////////////////////////////////////////////
	if (bActiveBooster == true)
	{

	}
	else
	{
		if (input->IsPressMovement() == true)
		{
			float moveSpeed = specData->WalkSpeed;

			if (bRunning == true)
				moveSpeed = specData->RunSpeed;

			if (input->Pressed(GamePlayerKey::MoveForward))
			{
				if (input->Pressed(GamePlayerKey::MoveLeft))
					moveDirection = D3DXVECTOR3(-1, 0, 1);
				else if (input->Pressed(GamePlayerKey::MoveRight))
					moveDirection = D3DXVECTOR3(1, 0, 1);
				else
					moveDirection = D3DXVECTOR3(0, 0, 1);
			}//MoveForward
			else if (input->Pressed(GamePlayerKey::MoveBackward))
			{
				if (input->Pressed(GamePlayerKey::MoveLeft))
					moveDirection = D3DXVECTOR3(-1, 0, -1);
				else if (input->Pressed(GamePlayerKey::MoveRight))
					moveDirection = D3DXVECTOR3(1, 0, -1);
				else
					moveDirection = D3DXVECTOR3(0, 0, -1);
			}//MoveBackward
			else
			{
				if (input->Pressed(GamePlayerKey::MoveLeft))
					moveDirection = D3DXVECTOR3(-0.5, 0, 0);
				else if (input->Pressed(GamePlayerKey::MoveRight))
					moveDirection = D3DXVECTOR3(0.5, 0, 0);
				else
					moveDirection = D3DXVECTOR3(0, 0, 0);
			}

			D3DXVec3Normalize(&moveDirection, &moveDirection);
			velocity = moveDirection * (moveSpeed * (D3DXVec3Length(&moveDirection) * 0.5f));

			bGoing = true;
		}//IsPressMovement
		else
		{
			moveDirection = D3DXVECTOR3(0, 0, 0);
			bGoing = false;
		}

		ActionMovement(moveDirection);
	}

	if (bGoing == true)
		this->velocity = velocity;
	else
		this->velocity = D3DXVECTOR3(0, 0, 0);
}

void GamePlayer::LoadAnimation(wstring path)
{
	UINT lowerAnimCount = (UINT)LowerAction::Count;
	UINT upperAnimCount = (UINT)UpperAction::Count;

	indexLowerAnimations.assign(lowerAnimCount, UINT());
	indexUpperAnimations.assign(upperAnimCount, UINT());

	//Lower Animation
	{
		indexLowerAnimations[(UINT)LowerAction::Idle] = AddClip(path + L"Low_Idle.anim");
		indexLowerAnimations[(UINT)LowerAction::Run] = AddClip(path + L"Low_Run.anim");
		indexLowerAnimations[(UINT)LowerAction::Damage] = AddClip(path + L"Low_Damage.anim");
		indexLowerAnimations[(UINT)LowerAction::Walk] = AddClip(path + L"Low_Walk.anim");
		indexLowerAnimations[(UINT)LowerAction::LeftTurn] = AddClip(path + L"Low_TurnLeft.anim");
		indexLowerAnimations[(UINT)LowerAction::RightTurn] = AddClip(path + L"Low_TurnRight.anim");
		indexLowerAnimations[(UINT)LowerAction::BackWalk] = AddClip(path + L"Low_WalkBack.anim");
		indexLowerAnimations[(UINT)LowerAction::ForwardDead] = AddClip(path + L"Low_DeathFront.anim");
		indexLowerAnimations[(UINT)LowerAction::BackwardDead] = AddClip(path + L"Low_DeathBack.anim");
		indexLowerAnimations[(UINT)LowerAction::LeftDead] = AddClip(path + L"Low_DeathLeft.anim");
		indexLowerAnimations[(UINT)LowerAction::RightDead] = AddClip(path + L"Low_DeathRight.anim");

		indexLowerAnimations[(UINT)LowerAction::BoosterPrepare] = AddClip(path + L"Low_BoosterStart.anim");
		indexLowerAnimations[(UINT)LowerAction::BoosterActive] = AddClip(path + L"Low_BoosterMove.anim");
		indexLowerAnimations[(UINT)LowerAction::BoosterFinish] = AddClip(path + L"Low_BoosterEnd.anim");
		indexLowerAnimations[(UINT)LowerAction::BoosterBreak] = AddClip(path + L"Low_BoosterMiss.anim");
		indexLowerAnimations[(UINT)LowerAction::BoosterLeftTurn] = AddClip(path + L"Low_BoosterTurnLeft.anim");
		indexLowerAnimations[(UINT)LowerAction::BoosterRightTurn] = AddClip(path + L"Low_BoosterTurnRight.anim");
	}

	//Upper Animation
	{
		indexUpperAnimations[(UINT)UpperAction::Idle] = AddClip(path + L"Up_Idle.anim");
		indexUpperAnimations[(UINT)UpperAction::Run] = AddClip(path + L"Up_Run.anim");
		indexUpperAnimations[(UINT)UpperAction::Damage] = AddClip(path + L"Up_Damage.anim");
		indexUpperAnimations[(UINT)UpperAction::WeaponChange] = AddClip(path + L"Up_Change.anim");

		indexUpperAnimations[(UINT)UpperAction::ForwardNonFire] = AddClip(path + L"Up_NonAttackFront.anim");
		indexUpperAnimations[(UINT)UpperAction::LeftNonFire] = AddClip(path + L"Up_NonAttackLeft.anim");
		indexUpperAnimations[(UINT)UpperAction::RightNonFire] = AddClip(path + L"Up_NonAttackRight.anim");

		indexUpperAnimations[(UINT)UpperAction::ForwardMachineGunFire] = AddClip(path + L"Up_AttackFrontBase.anim");
		indexUpperAnimations[(UINT)UpperAction::LeftMachineGunFire] = AddClip(path + L"Up_AttackLeftBase.anim");
		indexUpperAnimations[(UINT)UpperAction::RightMachineGunFire] = AddClip(path + L"Up_AttackRightBase.anim");
		indexUpperAnimations[(UINT)UpperAction::ReloadMachineGun] = AddClip(path + L"Up_ReloadBase.anim");

		indexUpperAnimations[(UINT)UpperAction::ForwardShotgunFire] = AddClip(path + L"Up_AttackFrontShotgun.anim");
		indexUpperAnimations[(UINT)UpperAction::LeftShotgunFire] = AddClip(path + L"Up_AttackLeftShotgun.anim");
		indexUpperAnimations[(UINT)UpperAction::RightShotgunFire] = AddClip(path + L"Up_AttackRightShotgun.anim");
		indexUpperAnimations[(UINT)UpperAction::ReloadShotgun] = AddClip(path + L"Up_ReloadShotgun.anim");

		indexUpperAnimations[(UINT)UpperAction::ForwardHandgunFire] = AddClip(path + L"Up_AttackFrontHandgun.anim");
		indexUpperAnimations[(UINT)UpperAction::LeftHandgunFire] = AddClip(path + L"Up_AttackLeftHandgun.anim");
		indexUpperAnimations[(UINT)UpperAction::RightHandgunFire] = AddClip(path + L"Up_AttackRightHandgun.anim");
		indexUpperAnimations[(UINT)UpperAction::ReloadHandgun] = AddClip(path + L"Up_ReloadHandgun.anim");

		indexUpperAnimations[(UINT)UpperAction::ForwardDead] = AddClip(path + L"Up_DeathFront.anim");
		indexUpperAnimations[(UINT)UpperAction::BackwardDead] = AddClip(path + L"Up_DeathBack.anim");
		indexUpperAnimations[(UINT)UpperAction::LeftDead] = AddClip(path + L"Up_DeathLeft.anim");
		indexUpperAnimations[(UINT)UpperAction::RightDead] = AddClip(path + L"Up_DeathRight.anim");

		indexUpperAnimations[(UINT)UpperAction::BoosterPrepare] = AddClip(path + L"Up_BoosterStart.anim");
		indexUpperAnimations[(UINT)UpperAction::BoosterActive] = AddClip(path + L"Up_BoosterMove.anim");
		indexUpperAnimations[(UINT)UpperAction::BoosterFinish] = AddClip(path + L"Up_BoosterEnd.anim");
		indexUpperAnimations[(UINT)UpperAction::BoosterBreak] = AddClip(path + L"Up_BoosterMiss.anim");
		indexUpperAnimations[(UINT)UpperAction::BoosterLeftTurn] = AddClip(path + L"Up_BoosterTurnLeft.anim");
		indexUpperAnimations[(UINT)UpperAction::BoosterRightTurn] = AddClip(path + L"Up_BoosterTurnRight.anim");
	}

	runDurationTime = GetClip(indexLowerAnimations[(UINT)LowerAction::Run])->Duration;
	walkDurationTime = GetClip(indexLowerAnimations[(UINT)LowerAction::Walk])->Duration;
	boosterFinishDurationTime = GetClip(indexLowerAnimations[(UINT)LowerAction::BoosterFinish])->Duration;
	boosterBreakDurationTime = GetClip(indexLowerAnimations[(UINT)LowerAction::BoosterBreak])->Duration;
	weaponChangeDurationTime = GetClip(indexUpperAnimations[(UINT)UpperAction::WeaponChange])->Duration;
}

void GamePlayer::PlayLowerAction(LowerAction action)
{
	PlayLowerAction(action, 0.0f);
}

void GamePlayer::PlayLowerAction(LowerAction action, float startTime)
{
	AnimationPlayMode mode = AnimationPlayMode::Repeat;
	float blendTime = 0.0f;

	switch (action)
	{
		case LowerAction::Idle:
			blendTime = 0.5f;
			break;
		case LowerAction::Run:
			blendTime = 0.3f;
			break;
		case LowerAction::Damage:
			mode = AnimationPlayMode::Once;
			blendTime = 0.2f;
			break;
		case LowerAction::Walk:
			blendTime = 0.3f;
			break;
		case LowerAction::BackWalk:
			blendTime = 0.3f;
			break;

		case LowerAction::LeftTurn:
		case LowerAction::RightTurn:
			blendTime = 0.5f;
			break;

		case LowerAction::ForwardDead:
		case LowerAction::BackwardDead:
		case LowerAction::LeftDead:
		case LowerAction::RightDead:
			mode = AnimationPlayMode::Once;
			blendTime = 0.2f;
			break;

		case LowerAction::BoosterPrepare:
		case LowerAction::BoosterActive:
		case LowerAction::BoosterFinish:
		case LowerAction::BoosterBreak:
		case LowerAction::BoosterLeftTurn:
		case LowerAction::BoosterRightTurn:
			mode = AnimationPlayMode::Once;
			blendTime = 0.2f;
			break;
	}
	Play(indexLowerAnimations[(UINT)action], startTime, blendTime, 1, mode);

	currentLowerAction = action;
	prepareLowerAction = LowerAction::Unknown;
	bOverwriteLowerAction = false;
}

void GamePlayer::PlayUpperAction(UpperAction action)
{
	PlayUpperAction(action, 0.0f);
}

void GamePlayer::PlayUpperAction(UpperAction action, float startTime)
{
	AnimationPlayMode mode = AnimationPlayMode::Repeat;
	float blendTime = 0.0f;

	switch (action)
	{
		case GamePlayer::UpperAction::Idle:
			blendTime = 0.5f;
			break;
		case GamePlayer::UpperAction::Run:
			blendTime = 0.3f;
			break;
		case GamePlayer::UpperAction::Damage:
			mode = AnimationPlayMode::Once;
			blendTime = 0.2f;
			break;
		case GamePlayer::UpperAction::WeaponChange:
			mode = AnimationPlayMode::Once;
			blendTime = 0.2f;
			break;

		case GamePlayer::UpperAction::ForwardNonFire:
		case GamePlayer::UpperAction::LeftNonFire:
		case GamePlayer::UpperAction::RightNonFire:
			mode = AnimationPlayMode::Once;
			blendTime = 0.5f;
			break;

		case GamePlayer::UpperAction::ForwardMachineGunFire:
		case GamePlayer::UpperAction::LeftMachineGunFire:
		case GamePlayer::UpperAction::RightMachineGunFire:
		case GamePlayer::UpperAction::ForwardShotgunFire:
		case GamePlayer::UpperAction::LeftShotgunFire:
		case GamePlayer::UpperAction::RightShotgunFire:
		case GamePlayer::UpperAction::ForwardHandgunFire:
		case GamePlayer::UpperAction::LeftHandgunFire:
		case GamePlayer::UpperAction::RightHandgunFire:
			mode = AnimationPlayMode::Once;
			blendTime = 0.5f;
			break;

		case GamePlayer::UpperAction::ReloadMachineGun:
		case GamePlayer::UpperAction::ReloadShotgun:
		case GamePlayer::UpperAction::ReloadHandgun:
			mode = AnimationPlayMode::Once;
			blendTime = 0.5f;
			break;

		case GamePlayer::UpperAction::ForwardDead:
		case GamePlayer::UpperAction::BackwardDead:
		case GamePlayer::UpperAction::LeftDead:
		case GamePlayer::UpperAction::RightDead:
			mode = AnimationPlayMode::Once;
			blendTime = 0.2f;
			break;

		case GamePlayer::UpperAction::BoosterPrepare:
		case GamePlayer::UpperAction::BoosterActive:
		case GamePlayer::UpperAction::BoosterFinish:
		case GamePlayer::UpperAction::BoosterBreak:
		case GamePlayer::UpperAction::BoosterLeftTurn:
		case GamePlayer::UpperAction::BoosterRightTurn:
			mode = AnimationPlayMode::Once;
			blendTime = 0.2f;
			break;
	}
	Play(indexUpperAnimations[(UINT)action], startTime, blendTime, 1.0f, mode);

	currentUpperAction = action;
	prepareUpperAction = UpperAction::Unknown;
	bOverwriteUpperAction = false;
}

void GamePlayer::ActionMovement(D3DXVECTOR3 direction)
{
	bool bMove = true;

	if (direction.z > 0.0f)
	{
		if (direction.x < 0.0f)
			rootRotationAngle = -35.0f;
		else if (direction.x > 0.0f)
			rootRotationAngle = 35.0f;
		else
			rootRotationAngle = 0.0f;

		if (bRunning == true)
		{
			if (currentLowerAction != LowerAction::Run)
				prepareLowerAction = LowerAction::Run;
		}
		else
		{
			if (currentLowerAction != LowerAction::Walk)
				prepareLowerAction = LowerAction::Walk;
		}
	}//direction.z > 0.0f
	else if (direction.z < 0.0f)
	{
		if (direction.x < 0.0f)
			rootRotationAngle = -30.0f;
		else if (direction.x > 0.0f)
			rootRotationAngle = 30.0f;
		else
			rootRotationAngle = 0.0f;

		if (currentLowerAction != LowerAction::BackWalk)
			prepareLowerAction = LowerAction::BackWalk;
	}//direction.z < 0.0f
	else
	{
		if (direction.x < 0.0f || direction.x > 0.0f)
		{
			if (direction.x < 0.0f)
			{
				rootRotationAngle = -65;

				if (currentLowerAction != LowerAction::LeftTurn)
					prepareLowerAction = LowerAction::LeftTurn;
			}
			else if (direction.x > 0.0f)
			{
				rootRotationAngle = 65;
				
				if (currentLowerAction != LowerAction::RightTurn)
					prepareLowerAction = LowerAction::RightTurn;
			}
		}//direction.z
		else
		{
			bMove = false;

			if (currentLowerAction != LowerAction::Idle)
				prepareLowerAction = LowerAction::Idle;

			rootRotationAngle = 0.0f;
			moveElapsedTime = 0.0f;
		}
	}
}
