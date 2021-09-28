class Vector3;
class Player;
class LocalPlayer {

private:
	LocalPlayer();

public:
	static LocalPlayer* Get();
	int GetHealth();
	int GetTeam();
	float GetDistance(Player* player);
	Vector3 GetOrigin();
	void AimAt(Player* target);
};



