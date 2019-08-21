#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "functions.h"



int main(void)
{
	int userBet, winOrLose, moneyInWallet;
	int keepPlaying = TRUE;
	int option;
	char user[100];

	srand((unsigned)time(NULL));
	while (keepPlaying)
	{
		printf("WELCOME!\nTHE RULES :\n");
		printf("if you roll 7 or 11 you win\nif you roll 2,3 or 12 you lose\n");
		printf("if you roll any other # you roll for point which means\n");
		printf("if you roll the same  # you win but if you roll 7 you lose\n");
		printf("GOOD LUCK!!\n\n");


		printf("1. Create a new user\n");
		printf("2. Load \n");
		printf("3. Play as a guest\n");
		printf("Please choose one of the three options (Enter 1,2 or 3): ");
		scanf("%d", &option);
		printf("\n");

		if (option == 1)
			moneyInWallet = createNewWallet(user);

		if (option == 2)
			moneyInWallet = getUserWallet(user);

		if (option == 3)
			moneyInWallet = getGuestWallet();


		if (moneyInWallet < 0)
		{
			printf("Error loading your wallet\n");
			printf("Goodbye!!\n\n");
			system("PAUSE");
			return 0;
		}

		while (keepPlaying == TRUE && moneyInWallet >= 5)
		{
			printf("\nYou have $%d in your wallet.\n", moneyInWallet);
			userBet = makeBet(moneyInWallet);
			winOrLose = playRound();

			moneyInWallet = walletBa(userBet, moneyInWallet, winOrLose);

			if (moneyInWallet < 5)
			{
				if (option == 3)
				{
					break;
				}
				printf("You balance is so low. The dealer is giving you $350 to continue playing\n");
				moneyInWallet += 350;
			}

			keepPlaying = doAgain();
		}

		if (moneyInWallet == 0)
			printf("You lost all your money goodbye!!\n\n");
		else if (moneyInWallet < 5)
			printf("You cannot play anymore you only have $%d left, goodbye!!\n\n", moneyInWallet);
		else
		{
			printf("You have $%d left in your wallet. Goodbye!\n\n", moneyInWallet);
			if (option != 3)
				updateWallet(moneyInWallet, user);
		}
		if (option != 3)
			break;
		keepPlaying = doAgain();
		printf("\n\n");
	}

	system("PAUSE");
	return 0;
}
