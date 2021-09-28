class Vector3;
class Player {
private:
	Player();

public:
	static Player* Get(int index);
	int GetHealth();
	int GetTeam();
	Vector3 GetBones();
};