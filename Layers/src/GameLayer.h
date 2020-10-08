#pragma once
#include "Layer.h"
#include "../../Tetris/src/Tetromino.h"
#include "../../util/src/Button.h"

#include <queue>
#include <functional>

class GameLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutdown() override;

	virtual void OnUpdate() override;
	virtual void OnEvent(sf::Event& event) override;
	void SpawnNextBlock();
private:
	void DrawUsername(sf::RenderWindow& window);
	void DrawPoints(sf::RenderWindow& window, int points);
	int GetColorInt(Tetromino tetromino);
	TetrominoType GetTypeFromNumeration(int number);
	bool CheckGameOver(Tetromino curr);
	void PaintGameBoardRed(sf::RenderWindow& window);
	void DrawGameBoard(sf::RenderWindow& window);
	void CheckAndFillQueue(std::deque<int>& deque);
	Tetromino CreateTetromino(std::deque<int>& deque);
	void CommitBlock(const Tetromino& tetromino);
	void ClearRow(sf::RenderWindow& window);
private:
	Tetromino m_CurrentTetromino;
	Tetromino m_NextTetromino;
	std::deque<int> m_Tetromino_queue;

	bool m_CanPlay = true;

	struct TimedFunction
	{
		float Time = 0.0f;
		std::function<void()> Function;
	};

	std::vector<TimedFunction> m_TimedFunctionQueue;

	sf::Clock clock;
	float m_LastTime = 0.0f;
	int points = 0;
	std::unique_ptr<Button> m_PlayAgainButton;
	bool m_db_updated = false;
	std::unique_ptr<Button> m_BackButton;
	sf::Text m_NextTetrominoText;
	sf::RectangleShape m_NextTetrominoBox;

	float m_LastFrameTime = 0.0f;

	float m_Delay = 0.0f;
private:
	static bool s_GameOver;
};