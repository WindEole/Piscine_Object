/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <iderighe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:27:25 by iderighe          #+#    #+#             */
/*   Updated: 2024/03/29 17:35:46 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bank.hpp"

/*
  Donc, dans notre fichier de base DivideAndRule, nous avons deux structures
  Account et Bank, et il faut encapsuler les méthodes (cad les rendres public
  private ou protected).
  ATTENTION : l'encapsulation dans une structure (struct) n'est possible qu'à
  partir de C++11 ! Donc on va transformer nos struct en class pour std 98
*/

class Bank; // Déclaration anticipée de la classe Bank

class Account
{
	friend class Bank; // Déclaration de la classe en tant qu'ami

	public:
		Account(std::string name, Bank& bank);	// constructeur by string
		~Account(void);							// destructeur

		Account	&operator=(Account const &rhs);	// surcharge d'assignation
		
		// Getter
		const std::string& 	getOwnerName() const;
		int 				getAccountNb() const;
		int					getAccountValue() const;
		bool				getLoanBool() const;
		int					getLoanValue() const;
		const std::string&	getBankName() const;

		// Member
// It must be impossible to add money to a client account without going through the bank
		void				addMoney(Bank& bank, int value);
		void				askForLoan(Bank& bank, int value);

	private:
		std::string	_ownerName;
		int 		_uniqId;
		int 		_value;
		bool 		_loan;
		int			_loanValue;
		std::string	_bankName;

	// friend std::ostream& operator << (std::ostream& p_os, const Account& p_account)
	// {
	// 	p_os << "[" << p_account._uniqId << "] - [" << p_account._value << "]";
	// 	return (p_os);
	// }
};



// struct Account
// {
// 	int id;
// 	int value;

// 	Account() :
// 		id(-1),
// 		value(0)
// 	{
	
// 	}

// 	friend std::ostream& operator << (std::ostream& p_os, const Account& p_account)
// 	{
// 		p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
// 		return (p_os);
// 	}
// };
