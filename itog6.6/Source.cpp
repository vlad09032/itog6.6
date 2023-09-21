#include<iostream>
#include<array>
#include<cstdlib>
enum BlackJack
{
	BLACKJACK_PLAYERWIN,
	BLACKJACK_DILERWIN,
	BLACKJACK_NICHIA
};

enum CardDostoinstvo
{
	DOSTOINSTVO_2,
	DOSTOINSTVO_3,
	DOSTOINSTVO_4,
	DOSTOINSTVO_5,
	DOSTOINSTVO_6,
	DOSTOINSTVO_7,
	DOSTOINSTVO_8,
	DOSTOINSTVO_9,
	DOSTOINSTVO_10,
	DOSTOINSTVO_VALET,
	DOSTOINSTVO_DAMA,
	DOSTOINSTVO_KING,
	DOSTOINSTVO_TUZ,
	MAX_DOSTOINSTVO
};

enum CardMast
{
	MAST_TREF,
	MAST_BUBN,
	MAST_CHERVY,
	MAST_PIKI,
	MAX_MAST
};

struct Card
{
	CardDostoinstvo dostoinstvo;
	CardMast mast;
};

void printCard(const Card &card)
{
		switch (card.dostoinstvo)
		{
		case DOSTOINSTVO_2:		std::cout << "2";
			break;
		case DOSTOINSTVO_3:		std::cout << "3";
			break;
		case DOSTOINSTVO_4:		std::cout << "4";
			break;
		case DOSTOINSTVO_5:		std::cout << "5";
			break;
		case DOSTOINSTVO_6:		std::cout << "6";
			break;
		case DOSTOINSTVO_7:		std::cout << "7";
			break;
		case DOSTOINSTVO_8:		std::cout << "8";
			break;
		case DOSTOINSTVO_9:		std::cout << "9";
			break;
		case DOSTOINSTVO_10:	std::cout << "10";
			break;
		case DOSTOINSTVO_VALET: std::cout << "V";
			break;
		case DOSTOINSTVO_DAMA:	std::cout << "D";
			break;
		case DOSTOINSTVO_KING:	std::cout << "K";
			break;
		case DOSTOINSTVO_TUZ:	std::cout << "T";
			break;

		}
		switch (card.mast)
		{
		case MAST_TREF:		std::cout << "T";
			break;
		case MAST_BUBN:		std::cout << "B";
			break;
		case MAST_CHERVY:	std::cout << "C";
			break;
		case MAST_PIKI:		std::cout << "P";
			break;
		}
}

void swapCard(Card &cardone, Card &cardtwo)
{
	Card cardtepm = cardone;
	cardone = cardtwo;
	cardtwo = cardtepm;
}

void printDeck(const std::array<Card, 52> &deck)
{
	for (const auto card : deck)
	{
		printCard(card);
		std::cout << " ";
	}
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// –авномерно распредел€ем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck( std::array<Card,52> &deck)
{
	
	for (int index{0};index<52; ++index)
	{
		int swapindex = getRandomNumber(1, 52);
		swapCard(deck[index], deck[swapindex]);
	}
}



int getCardValue(const Card &numbercard)
{
	int znach{ 0 };
	switch (numbercard.dostoinstvo)
	{
	case DOSTOINSTVO_2:		znach = 2;
		break;
	case DOSTOINSTVO_3:		znach = 3;
		break;
	case DOSTOINSTVO_4:		znach = 4;
		break;
	case DOSTOINSTVO_5:		znach = 5;
		break;
	case DOSTOINSTVO_6:		znach = 6;
		break;
	case DOSTOINSTVO_7:		znach = 7;
		break;
	case DOSTOINSTVO_8:		znach = 8;
		break;
	case DOSTOINSTVO_9:		znach = 9;
		break;
	case DOSTOINSTVO_10:	znach = 10;
		break;
	case DOSTOINSTVO_VALET: znach = 10;
		break;
	case DOSTOINSTVO_DAMA:	znach = 10;
		break;
	case DOSTOINSTVO_KING:	znach = 10;
		break;
	case DOSTOINSTVO_TUZ:	znach = 11;
		break;
	}
	return znach;
}

BlackJack playBlackjack(const std::array<Card, 52>& deck)
{
	const Card* cardPtr = &deck[0];
	int resultIgrok{ 0 }, resultDiler{ 0 };
	resultDiler += getCardValue(*cardPtr++);
	bool opros;
	do
	{
		resultIgrok += getCardValue(*cardPtr++);
		std::cout << " оличество очков у игрока: " << resultIgrok << std::endl;
		std::cout << "≈ще? ";
		std::cin >> opros;
	} while (opros == 1);

	if (resultIgrok > 22)
	{
		std::cout << "превышено количество очков у игрока" << std::endl;
		return BLACKJACK_DILERWIN;
	}
	else
	{
		do
		{
			resultDiler += getCardValue(*cardPtr++);
			std::cout << " оличество очков у дилера: " << resultDiler << std::endl;
			std::cout << "≈ще? ";
			std::cin >> opros;
		} while (opros == 1);
		if (resultDiler < 17) 
		{
			std::cout << "вы не набрали нужное минимальное количество очков, вам добавлена карта автоматически " << std::endl;
			do
			{
				resultDiler += getCardValue(*cardPtr++);
				std::cout << " оличество очков у дилера: " << resultDiler << std::endl;
				std::cout << "≈ще? ";
				std::cin >> opros;
			} while (opros == 1);
			
		}
		if (resultDiler > 22)
		{
			std::cout << "превышено количество очков у дилера " << resultDiler << std::endl;
			return BLACKJACK_PLAYERWIN;
		}
		if (resultIgrok = resultDiler)
			return BLACKJACK_NICHIA;
		else
		{
			if (resultIgrok > resultDiler)
				return BLACKJACK_PLAYERWIN;
			else
				return BLACKJACK_DILERWIN;
		}
		
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();
	setlocale(LC_ALL, "");

	std::array<Card, 52> deck;
	int card{ 0 };
	for (int dost{ 0 }; dost < MAX_DOSTOINSTVO; ++dost)
	{
		for (int mas{ 0 }; mas < MAX_MAST; ++mas)
		{
			deck[ card ].dostoinstvo = static_cast<CardDostoinstvo>(dost);
			deck[ card ].mast = static_cast<CardMast>(mas);
			++card;
		}
	}
	//printDeck(deck);

	shuffleDeck(deck);

	bool opros;
	/*do
	{
		std::cout << "¬ывести перетасованный массив? 1 - Yes or 0 - No ";
		std::cin >> opros;
	} while (!(opros == 1 || opros == 0 ));

	if (opros == 1)
		printDeck(deck);*/

	switch (playBlackjack(deck))
	{
	case BLACKJACK_PLAYERWIN: std::cout << "выиграл игрок";
		break;
	case BLACKJACK_DILERWIN: std::cout << "выиграл дилер";
		break;
	case BLACKJACK_NICHIA: std::cout << "ничь€";
		break;

	}
}