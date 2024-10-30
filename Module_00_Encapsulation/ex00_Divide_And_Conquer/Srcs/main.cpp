/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <iderighe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:27:38 by iderighe          #+#    #+#             */
/*   Updated: 2024/03/29 18:27:39 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Account.hpp"
#include "../Includes/Bank.hpp"

#define RESET "\e[0m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define PURPLE "\e[0;35m"
#define CYAN "\e[0;36m"

void display(Bank& bank)
{
	std::cout << std::endl;
	std::cout << "----------  " << RED << "Bank " << bank.getBankName() << RESET << "  ----------" << std::endl;
	std::cout << "Fonds disponibles = " << bank.getLiquidity() << std::endl;
	// std::cout << "Clients : " << std::endl;
	
	std::vector<Account *> accountList = bank.getClientList();
	if (accountList.empty())
		std::cout << "Nous n'avons pas encore de clients..." << std::endl;
	std::vector<Account *>::iterator it = accountList.begin();
	for(; it != accountList.end(); it++)
	{
		std::cout << "	------  client : " << (*it)->getOwnerName() << "  ------" << std::endl;
		std::cout << "	id : " << (*it)->getAccountNb() << std::endl;
		std::cout << "	montant : " << (*it)->getAccountValue() << " piastres. " << std::endl;
		if ((*it)->getLoanBool())
			std::cout << "	Prêt accordé par la banque, pour un montant de " << (*it)->getLoanValue() << " piastres. " << std::endl;
		else
			std::cout << "	Pas d'emprunt en cours." << std::endl;
		std::cout << std::endl;
	}
	std::cout << "-----------------------------------" << std::endl;
	std::cout << std::endl;
}

void display(Account& account)
{
	std::cout << std::endl;
	std::cout << "------  " << GREEN << "client : " << account.getOwnerName() << RESET << "  ------" << std::endl;
	std::cout << "id : " << account.getAccountNb() << std::endl;
	std::cout << "montant : " << account.getAccountValue() << " piastres. " << std::endl;
	if (account.getLoanBool())
		std::cout << "Prêt accordé par la banque, pour un montant de " << account.getLoanValue() << " piastres. " << std::endl;
	else
		std::cout << "Pas d'emprunt en cours." << std::endl;
	std::cout << std::endl;
}

int main()
{
// On instancie les banques avec un nom et une mise de fonds de départ
	Bank Thieves("Thieves", 1500);
	display(Thieves);
	Bank Frauds("Frauds", 700);
	display(Frauds);

// On instancie les comptes avec un nom et la banque
	Account accountA = Account("Isabelle", Thieves);
	display(accountA);
	std::cout << YELLOW << "\nIsabelle met de l'argent sur son compte : " << RESET << std::endl;
	accountA.addMoney(Thieves, 200);
	std::cout << YELLOW << "\nIsabelle demande un prêt à la banque : " << RESET << std::endl;
	accountA.askForLoan(Thieves, 700);

	Account accountB = Account("Florian", Thieves);
	display(accountB);
	std::cout << YELLOW << "\nFlorian met de l'argent sur son compte : " << RESET << std::endl;
	accountB.addMoney(Thieves, 120);
	std::cout << YELLOW << "\nFlorian demande un prêt à la banque : " << RESET << std::endl;
	accountB.askForLoan(Thieves, 2000);
	std::cout << YELLOW << "\nFlorian demande un prêt à une banque dans laquelle il n'a pas ouvert de compte : " << RESET << std::endl;
	accountB.askForLoan(Frauds, 200);

	std::cout << YELLOW << "\nLa banque Frauds tente de récupérer le compte de Florian : " << RESET << std::endl;
	Frauds.addNewAccount(accountB);

	std::cout << YELLOW << "\nIsabelle tente de chiper de l'argent à la banque Frauds : " << RESET << std::endl; 
	accountA.addMoney(Frauds, 500);

	std::cout << YELLOW << "\nLa banque accorde un prêt sans que ce soit demandé par le client." << RESET << std::endl;
	Thieves.grantLoanToAccount(accountB.getAccountNb(), 350);

	display(Thieves);
	display(Frauds);
	
	display(accountA);
	display(accountB);

	return (0);
}
