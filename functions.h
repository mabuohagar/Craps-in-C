#define TRUE 1
#define FALSE 0
#define SLEEP 500
#define STARTING_BALANCE 1000
int rollDie(void);
int rollDice(void);
int playRound(void);
int getGuestWallet(void);
int getUserWallet(char user[100]);
int createNewWallet(char user[100]);
int makeBet(int);
int doAgain(void);
int walletBa(int, int, int);
void updateWallet(int, char user[100]);


/*
 * gives a random num from 1 to 6
 */
int rollDie(void) {
	return rand() % 6 + 1;
}

/*
 *gives a random num from 2 to 12
 */
int rollDice(void) {
	return rollDie() + rollDie();
}
/*
 *play one round of the game and returuns one or zero
 */
int playRound(void) {

	int ans = 2;
	int pointRolling;
	int rolling = rollDice();

	Sleep(SLEEP);
	printf("You rolled a %d\n", rolling);

	/* the rules are :
			if you roll 7 or 11 you win
			if you roll 2,3,12 you loose
			if you roll any other # you roll for point which means
			if you roll the same  # you win but if you roll 7 loose
			and you keep rolling tell you get the # or 7

	*/
	if (rolling == 7 || rolling == 11)
		ans = TRUE;

	else if (rolling == 2 || rolling == 3 || rolling == 12)
		ans = FALSE;

	else {
		printf("\nRolling for point: %d\n", rolling);

		Sleep(SLEEP);
		while (ans != FALSE && ans != TRUE) {


			pointRolling = rollDice();
			printf("You rolled a %d\n", pointRolling);

			Sleep(SLEEP);

			if (pointRolling == 7)
				ans = FALSE;
			else if (pointRolling == rolling)
				ans = TRUE;
		}
	}
	return ans;
}

/* Function: getWallet
* Prompts the user for the amount of money they have to play with – assumed to be
* measured in whole dollars. Rejects values that are not at least MIN_BET in size and
* prompts for another value until a value of size MIN_BET or greater is entered.
* Returns: amount of money entered by user (a positive, integer dollar value)
*/

int getGuestWallet(void) {

	int moneyInWallet;

	printf("How much money do you have to play with?\n");

	scanf("%d", &moneyInWallet);

	while (moneyInWallet < 5)
	{

		printf("Not enough funds\nHow much money do you have to play with?\n");
		scanf("%d", &moneyInWallet);
	}

	return moneyInWallet;
}

/* Function: makeBet
* Prompts user to make a bet (minimum value: MIN_BET; maximum value: amount in wallet).
* Keeps prompting user until a value of at least MIN_BET but no more than amount
* in wallet is entered.
* Parameter: wallet - the amount in the user's wallet
* Returns: user's bet (minimum MIN_BET)
*/

int makeBet(int moneyInWallet) {

	int userBet;

	printf("Place your bet (minimum $5) : ");
	scanf("%d", &userBet);
	while (1)
	{
		while (userBet < 5) {
			printf("The minimum bet is 5\n");
			printf("Place your bet (minimum $5) : ");
			scanf("%d", &userBet);
		}
		while (userBet > moneyInWallet) {
			printf("You don't have enough money, You only have $%d\n", moneyInWallet);
			printf("Place your bet (minimum $5) : ");
			scanf("%d", &userBet);
		}
		if (userBet <= moneyInWallet && userBet >= 5)
			break;
	}
	return userBet;
}

/* Function: doAgain
* Ask user if they want to play again.
* Returns: true if user wants to play again, false otherwise.
*/

int doAgain(void) {

	int ans;

	printf("Enter 1 to play again, 0 to quit: ");
	scanf("%d", &ans);
	printf("\n");

	return ans;
}

int walletBa(int bet, int moneyInWallet, int wOrL) {

	if (wOrL == TRUE) {
		moneyInWallet += bet;
		printf("You win :-)\n\n");
	}

	if (wOrL == FALSE) {
		moneyInWallet -= bet;
		printf("You lose :-(\n\n");
	}

	return moneyInWallet;
}
int getUserWallet(char user[100])
{

	FILE	*file1 = NULL;
	int error;
	int choice;
	char*file_name;
	int walletBalance;

	printf("Please enter the User name: ");
	scanf("%s", user);
	file_name = strcat(user, ".txt");

	error = fopen_s(&file1, file_name, "r+");
	if (error) {
		printf("The user file does't exist\n");
		printf("Would you like to create a new User? (1 for yes) :  ");
		scanf("%d", &choice);
		if (choice == 0)
		{
			return -1;
		}
		if (choice == 1)
		{
			walletBalance = createNewWallet(user);
		}
	}
	else
	{
		error = fscanf_s(file1, "%d", &walletBalance);
		if (!error)
		{
			printf("Error\n\n");
		}
		fclose(file1);
	}
	return walletBalance;
}

int createNewWallet(char user[100])
{


	FILE*file1 = NULL;
	int error;
	int choice;
	char*file_name;
	int walletBalance;


	printf("Please enter the New User name: ");
	scanf("%s", user);
	file_name = strcat(user, ".txt");

	error = fopen_s(&file1, file_name, "r");
	while (error == NULL)
	{
		fclose(file1);
		printf("The file alreay exists please choose another user name\n\n");

		printf("Please enter the New User name: ");
		scanf("%s", user);
		file_name = strcat(user, ".txt");

		error = fopen_s(&file1, file_name, "r");
	}
	fopen_s(&file1, file_name, "w+");
	fprintf(file1, "%d", STARTING_BALANCE);
	fclose(file1);
	fopen_s(&file1, file_name, "r");
	fscanf_s(file1, "%d", &walletBalance);
	fclose(file1);


	return walletBalance;

}
void updateWallet(int walletBalance, char user[100])
{
	FILE*file1 = NULL;
	char*file_name = user;

	fopen_s(&file1, file_name, "w");
	fprintf(file1, "%d", walletBalance);
	fclose(file1);
}
