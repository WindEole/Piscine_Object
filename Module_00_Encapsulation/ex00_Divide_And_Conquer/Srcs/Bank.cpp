/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <iderighe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:18:55 by iderighe          #+#    #+#             */
/*   Updated: 2024/03/29 18:22:43 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Bank.hpp"
#include "../Includes/Account.hpp"

/*
  Ici, on va définir la variable statique _nextAccountNb pour que toutes les
  instances de la classe Bank partagent la même variable
*/
int Bank::_nextAccountNb = 100; // valeur random, à modifier selon l'envie


//-----------------------   CONSTRUCTOR / DESTRUCTOR   -----------------------//

Bank::Bank(std::string bankName, int funds)
{
	this->_bankName = bankName;
	this->_liquidity = funds;

	// std::cout << "Bank constructor called : " << this->_bankName << " is created." << std::endl;
	return;
}

Bank::~Bank()
{
	// std::cout << "Bank Destructor called : " << this->_bankName << " is destroyed." << std::endl;
	return;
}

//------------------------------   SURCHARGES   ------------------------------//
// Est-ce utile ? 
Bank	&Bank::operator=(Bank const &rhs)
{
	// std::cout << "Assignment operator called" << std::endl;
	if (this == &rhs)
		return (*this);
	
	this->_bankName = rhs._bankName;
	return (*this);
}

//--------------------------------   GETTER   --------------------------------//

const std::string&		Bank::getBankName(void) const
{
	return (this->_bankName); 
}

int						Bank::getLiquidity(void) const
{
	return (this->_liquidity); 
}

int						Bank::getNextAccountNb(void) const
{
	return (this->_nextAccountNb); 
}

std::vector<Account *> 	Bank::getClientList(void) const
{
	return (this->clientAccounts);
}


//--------------------------------   SETTER   --------------------------------//

void	Bank::setNextAccountNb()
{
	// std::cout << "Last customer account number = " << this->_nextAccountNb << std::endl;
	this->_nextAccountNb++;
	// std::cout << "Next customer account = " << this->_nextAccountNb << std::endl;
	return;
}

void 	Bank::setLiquidity(int value)
{
	// std::cout << "BankLiquidity before prelevement = " << this->_liquidity << std::endl;
	this->_liquidity += value;
	// std::cout << "BankLiquidity after prelevement = " << this->_liquidity << std::endl;
	return;
}

//---------------------------   MEMBER FUNCTIONS   ---------------------------//

void	Bank::addNewAccount(Account& account)
{
	// 1) on vérifie si le compte appartient déjà à une banque
	if (account.getBankName() != "")
	{
		std::cout << "Ce compte est déjà enregistré dans une autre banque." << std::endl;
		return;
	}
	// 2) si pas de banque associée, on attribue le nom de la banque
	account._bankName = this->getBankName();
	// 2) entrer le new Account dans le tableau des comptes clients
	clientAccounts.push_back(&account);
	// 2) incrémenter le _nextAccountNumber pour le prochain client
	setNextAccountNb();
}

void	Bank::deleteAccount(int countId)
{
	// 1) On recupere le tableau des comptes
	std::vector<Account *> accountList = getClientList();
	// 2) On cherche le bon compte dans le tableau des comptes grace a countId
	std::vector<Account *>::iterator it = accountList.begin();
	for(; it != accountList.end(); it++)
	{
		if ((*it)->getAccountNb() == countId)
		{
			std::cout << "Le compte numéro " << (*it)->getAccountNb() << " appartenant à " << (*it)->getOwnerName() << " est supprimé." << std::endl;
			accountList.erase(it);
		}
	}
}

void	Bank::addMoneyToAccount(int countId, int val)
{
	// 1) On recupere le tableau des comptes
	std::vector<Account *> accountList = getClientList();
	// 2) On cherche le bon compte dans le tableau des comptes grace a countId
	std::vector<Account *>::iterator it = accountList.begin();
	for(; it != accountList.end(); it++)
	{
		if ((*it)->getAccountNb() == countId)
		{
			// 3) On ajoute la somme au compte, avec un prelevement de 5% du montant
				// 3.a) calcul des 5%
			int prlvt = val * 5 / 100;
				// 3.b) ajout des 5% a Liquidity de la banque
			setLiquidity(prlvt);
				// 3.c) ajout de la somme minorée de 5% au compte
			int new_val = val - prlvt;
			(*it)->_value += new_val;
			std::cout << "Vous souhaitez déposer " << val << " piastres. " << std::endl;
			std::cout << "Comme le stipule notre contrat, nous prenons 5% de votre dépôt, soit " << prlvt << " piastres. " << std::endl;
			std::cout << "Nous mettons donc la somme de " << new_val << " piastres sur votre compte, qui est désormais de " << (*it)->_value << " piastres. " << std::endl;
		}
	}
}

std::string	Bank::grantLoanToAccount(int countId, int val)
{
	std::cout << "Vous avez sollicité un emprunt de " << val << " piastres auprès de notre établissement. " << std::endl;
	if (val >= this->_liquidity)
		return "Cependant, nous ne pouvons vous accorder ce prêt car nous n'avons pas les fonds...";
	std::vector<Account *> accountList = getClientList();
	std::vector<Account *>::iterator it = accountList.begin();
	for(; it != accountList.end(); it++)
	{
		if ((*it)->getAccountNb() == countId)
		{
			setLiquidity(-val); // on retire le montant du prêt des liquidités
			(*it)->_value += val; // on ajoute le montant du prêt au compte client
			(*it)->_loan = true; // on met à jour le bool du prêt du compte client
			(*it)->_loanValue += val; // on met à jour la valeur du prêt du compte client
			return "Suite à l'étude de votre dossier, le prêt est accordé.";
		}
	}
	return "Cependant, vous n'êtes pas notre client. Nous ne pouvons donc donner suite à votre demande. ";
}
