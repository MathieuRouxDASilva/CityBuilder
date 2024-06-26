#ifndef API_GAMEPLAY_ECONOMY_MANAGER_H_
#define API_GAMEPLAY_ECONOMY_MANAGER_H_


class EconomyManager
{
private:
	size_t economy_;

public:
	//constructor
	EconomyManager();

	//reduce/increase economy by a certain number
	void ReduceEconomyBy(size_t number);
	void IncreaseEconomyBy(size_t number);

	//Get -------------------
	[[nodiscard]] size_t economy() const;

};


#endif //API_GAMEPLAY_ECONOMY_MANAGER_H_
