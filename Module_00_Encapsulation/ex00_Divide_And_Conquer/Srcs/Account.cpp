/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <iderighe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:18:55 by iderighe          #+#    #+#             */
/*   Updated: 2024/03/29 18:22:54 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #pragma once

#include "../Includes/Account.hpp"

//-----------------------   CONSTRUCTOR / DESTRUCTOR   -----------------------//

Account::Account(std::string name, Bank& bank)
{
	this->_ownerName = name;
	this->_uniqId = bank.getNextAccountNb();
	this->_value = 0;
	this->_loan = false;
	this->_loanValue = 0;
	
	bank.addNewAccount(*this);

	// std::cout << "Account constructor called : " << this->_ownerName << " is created." << std::endl;
	return;
}

Account::~Account()
{
	// std::cout << "Account Destructor called : " << this->_ownerName << " is destroyed." << std::endl;
	return;
}

//------------------------------   SURCHARGES   ------------------------------//

Account	&Account::operator=(Account const &rhs)
{
	// std::cout << "Assignment operator called" << std::endl;
	if (this == &rhs)
		return (*this);
	
	this->_ownerName = rhs._ownerName;
	this->_uniqId = rhs._uniqId;
	this->_value = rhs._value;
	return (*this);
}

//--------------------------------   GETTER   --------------------------------//

const std::string&	Account::getOwnerName(void) const
{
	return (this->_ownerName); 
}

int					Account::getAccountNb(void) const
{
	return (this->_uniqId); 
}

int					Account::getAccountValue(void) const
{
	return (this->_value); 
}

bool				Account::getLoanBool() const
{
	return (this->_loan);
}

int					Account::getLoanValue() const
{
	return (this->_loanValue);
}

const std::string&	Account::getBankName() const
{
	return (this->_bankName);
}

//---------------------------   MEMBER FUNCTIONS   ---------------------------//

void		Account::addMoney(Bank& bank, int value)
{
	// On vérifie que le compte est bien dans cette banque
	if (this->getBankName() != bank.getBankName())
	{
		std::cout << "Vous n'avez pas de compte dans la banque " << bank.getBankName() << std::endl;
		return;
	}
	bank.addMoneyToAccount(this->_uniqId, value);
}

void		Account::askForLoan(Bank& bank, int value)
{
	// if (bank.getBankName() != this->_bankName)
	// {
	// 	std::cout << "Nous ne pouvons donner suite à votre demande car vous n'êtes pas client chez nous. " << std::endl;
	// }
	std::cout << bank.grantLoanToAccount(this->_uniqId, value) << std::endl;
}
