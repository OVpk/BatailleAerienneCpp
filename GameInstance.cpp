#include "GameInstance.h"
#include "Plane.h"
#include "Drone.h"
#include "Unit.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>


void GameInstance::InitBoard()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //pour initialiser random (trouvé sur internet mais ça me semble sale)

	SpawnTargetsRandom<Target>(TARGETS_PER_PLAYER, &p1);
	SpawnTargetsRandom<Drone>(DRONES_PER_PLAYER, &p1);
	SpawnTargetsRandom<Plane>(PLANES_PER_PLAYER, &p1);

	SpawnTargetsRandom<Target>(TARGETS_PER_PLAYER, &p2);
	SpawnTargetsRandom<Drone>(DRONES_PER_PLAYER, &p2);
	SpawnTargetsRandom<Plane>(PLANES_PER_PLAYER, &p2);
}

void GameInstance::StartGameLoop()
{
	InitBoard();

	bool isGamePlaying = true;
	Player* currentPlayer = &p1;

	while (isGamePlaying)
	{
		bool isEndTurn = false;

		while (!isEndTurn && isGamePlaying)
		{
			std::system("cls");
			std::cout << "\n --- Joueur Actuel : " << currentPlayer->color << currentPlayer->playerName << "\033[0m ---\n";
			renderer.DrawGrid(currentGrid);
			std::cout << "\n(Tapez Q pour quitter et revenir au menu principal)\n";

			std::cout << "\nEntrez les coordonnees d'une cellule (ligne-colone): \n";
			std::string input;
			std::getline(std::cin, input);

			if (!input.empty() && (input[0] == 'q' || input[0] == 'Q'))
			{
				isGamePlaying = false;
				break;
			}

			std::stringstream ss(input);
			int row, collumn;
			char delimiter;

			if (ss >> row >> delimiter >> collumn && delimiter == '-')
			{
				Target* target = currentGrid->getCell(row, collumn);

				if (target == nullptr)
				{
					std::cout << "\n[!] Case invalide ou vide. Appuyez sur Entree...\n";
					std::getline(std::cin, input);
					continue;
				}

				bool isOwner = (target->GetOwner() == currentPlayer);

				if (!isOwner)
				{
					std::system("cls");
					std::cout << "\n --- Joueur Actuel : " << currentPlayer->color << currentPlayer->playerName << "\033[0m ---\n";
					renderer.DrawGrid(currentGrid);

					Analyse(target, isOwner);

					std::cout << "\nAppuyez sur Entree pour continuer...\n";
					std::getline(std::cin, input);
				}
				else
				{
					isEndTurn = SelectActionMenu(target, currentPlayer, row, collumn);
				}
			}
			else
			{
				std::cout << "\n[!] Format invalide. Utilisez Ligne-Colonne (ex: 2-5). Appuyez sur Entree...\n";
				std::getline(std::cin, input);
			}
		}

		if (isGamePlaying)
		{
			currentPlayer = (currentPlayer == &p1) ? &p2 : &p1;
		}
	}

	std::system("cls");
	std::cout << "Retour au menu principal...\n";
}

bool GameInstance::SelectActionMenu(Target* target, Player* currentPlayer, int row, int collumn)
{
	bool isActionChoiced = false;
	bool isEndTurn = false;

	while (!isActionChoiced)
	{
		std::system("cls");
		std::cout << "\n --- Joueur Actuel : " << currentPlayer->color << currentPlayer->playerName << "\033[0m ---\n";
		renderer.DrawGrid(currentGrid);

		std::cout << "\nCible selectionnee :" << row << "-" << collumn << ".\n";
		
		Unit* unit = dynamic_cast<Unit*>(target);
		
		if (unit)
		{
			std::cout << "1. Analyser | 2. Deplacer | 3. Attaquer | 4. Annuler\n";
		}
		else
		{
			std::cout << "1. Analyser | 4. Annuler\n";
		}

		std::cout << "Votre choix :\n";

		std::string input;
		std::getline(std::cin, input);
		char choice = input.empty() ? '0' : input[0];

		switch (choice)
		{
		case '1':
			Analyse(target, true);
			std::cout << "\nAppuyez sur Entree pour continuer...\n";
			std::getline(std::cin, input);
			break;
		case '2':
		{
			if (!unit) break;
			if (Move(unit, row, collumn))
			{
				isActionChoiced = true;
				isEndTurn = true;

				std::system("cls");
				std::cout << "\n --- Joueur Actuel : " << currentPlayer->color << currentPlayer->playerName << "\033[0m ---\n";
				renderer.DrawGrid(currentGrid);

				std::cout << "\nDeplacement reussi !\n";
			}
			std::cout << "\nAppuyez sur Entree pour continuer...\n";
			std::getline(std::cin, input);
			break;
		}
		case '3':
			if (!unit) break;
			if (Attack(unit, row, collumn))
			{
				isActionChoiced = true;
				isEndTurn = true;

				std::cout << "\nAppuyez sur Entree pour terminer votre tour...";
				std::getline(std::cin, input);

				std::system("cls");
				std::cout << "\n --- Joueur Actuel : " << currentPlayer->color << currentPlayer->playerName << "\033[0m ---\n";
				renderer.DrawGrid(currentGrid);

				std::cout << "\nAttaque terminee !\n";
			}
			std::cout << "\nAppuyez sur Entree pour continuer...\n";
			std::getline(std::cin, input);
			break;
		case '4':
			isActionChoiced = true;
			break;
		default:
			std::cout << "Choix Invalide\n";
			std::cout << "Appuyez sur Entree pour reessayer...\n";

			std::getline(std::cin, input);
			break;
		}
		
		
	}
	return isEndTurn;
}

void GameInstance::Analyse(Target* target, bool isOwner) const
{
#ifndef DEV_MODE
	if (!isOwner)
	{
		std::cout << "\nLe brouillard de guerre vous empéche de distinguer l'enemie...\n";
		return;
	}
#else
	if (!isOwner)
	{
		std::cout << "\n[DEV] Cible ennemie (Brouillard lever)";
	}
#endif

	std::cout << "\n PV : " << target->GetHealth();

	Unit* unit = dynamic_cast<Unit*>(target);
	if (unit)
	{
		std::cout << " | Attaque : " << unit->GetAttack();
	}
	std::cout << '\n';
}

bool GameInstance::Move(Unit* unit, int startRow, int startCollumn)
{
	if (!unit) return false;

	std::cout << "\nChoisissez une direction :\n"
		<< "0: Haut    1: Bas     2: Gauche  3: Droite\n"
		<< "4: Haut-G  5: Haut-D  6: Bas-G   7: Bas-D\n"
		<< "Votre choix : ";

	std::string input;
	std::getline(std::cin, input);
	char choice = input.empty() ? '9' : input[0];

	if (choice >= '0' && choice <= '7')
	{
		int directionValue = choice - '0';
		Direction dir = static_cast<Direction>(directionValue);
		std::optional<Position2D> newPos = unit->SimulateMove(dir, { startRow, startCollumn });

		if (newPos.has_value())
		{
			if (currentGrid->moveCell(startRow, startCollumn, newPos->row, newPos->col))
			{
				return true;
			}
			else
			{
				std::cout << "\nMouvement impossible\n";
				return false;
			}
		}
		else
		{
			std::cout << "\nCe type d'unitee ne peux pas se deplacer dans cette direction.\n";
		}
	}
	else
	{
		std::cout << "\nDirection invalide.\n";
	}

	return false;
}

bool GameInstance::Attack(Unit* unit, int startRow, int startCollumn)
{
	if (!unit) return false;

	std::cout << "\nChoisissez une direction d'attaque :\n"
		<< "0: Haut    1: Bas     2: Gauche  3: Droite\n"
		<< "4: Haut-G  5: Haut-D  6: Bas-G   7: Bas-D\n"
		<< "Votre choix : ";

	std::string input;
	std::getline(std::cin, input);
	char choice = input.empty() ? '9' : input[0];

	if (choice >= '0' && choice <= '7')
	{
		int directionValue = choice - '0';
		Direction dir = static_cast<Direction>(directionValue);

		std::vector<Position2D> hitPositions = unit->SimulateAttack(dir, {startRow, startCollumn});

		if (hitPositions.empty())
		{
			std::cout << "\nCe type d'unite ne peut pas attaquer dans cette direction.\n";
			return false;
		}

		bool hasHitSomething = false;

		for (const Position2D& position : hitPositions)
		{
			Target* targetHit = currentGrid->getCell(position.row, position.col);

			if (targetHit != nullptr)
			{
				std::cout << "\nCible touchee en : " << position.row << "-" << position.col << '\n';

				targetHit->TakeDamage(unit->GetAttack());
				std::cout << " Elle subit " << unit->GetAttack() << " degats. (PV restants : " << targetHit->GetHealth() << ")";

				if (targetHit->GetHealth() <= 0)
				{
					std::cout << "Cible detruite";

					currentGrid->removeCell(position.row, position.col);
				}

				hasHitSomething = true;
			}
		}

		if (!hasHitSomething)
		{
			std::cout << "\nL'attaque a frappe dans le vide\n";
		}

		return true;
	}
	else
	{
		std::cout << "\nDirection invalide.\n";
	}

	return false;
}


