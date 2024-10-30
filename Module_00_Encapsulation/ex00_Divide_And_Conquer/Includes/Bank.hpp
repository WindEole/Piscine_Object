/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <iderighe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:27:25 by iderighe          #+#    #+#             */
/*   Updated: 2024/03/29 17:54:15 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

/*
  Donc, dans notre fichier de base DivideAndRule, nous avons deux structures
  Account et Bank, et il faut encapsuler les méthodes (cad les rendres public
  private ou protected).
  ATTENTION : l'encapsulation dans une structure (struct) n'est possible qu'à
  partir de C++11 ! Donc on va transformer nos struct en class
*/

class Account; // Déclaration anticipée de la classe Account

class Bank
{
	public:
		Bank(std::string bankName, int funds); 	// constructeur par dêfaut
		~Bank(void); 							// destructeur
		
		Bank	&operator=(Bank const &rhs);	// surcharge d'assignation

		// Getter
		const std::string&		getBankName() const;
		int 					getLiquidity() const;
		int		 				getNextAccountNb() const;
		std::vector<Account *>	getClientList() const;

		// Setter
		void					setNextAccountNb();

		// Member
// The bank can create, delete and modify the accounts
		void 					addNewAccount(Account& account);
		void					deleteAccount(int countId);
// The bank receive 5% of each money inflow on these client accounts and It must be impossible to add money to a client account without going through the bank
		void					addMoneyToAccount(int countId, int val);
// The bank can give a loan to a customer, within the limits of its funds
		std::string				grantLoanToAccount(int countId, int val);

	private:
		// void 					addNewAccount(Account& account);
		void					setLiquidity(int value);

		std::string 			_bankName;
		static int 				_nextAccountNb;
		int 					_liquidity;
		std::vector<Account *> 	clientAccounts;	// tableau des comptes clients
};
