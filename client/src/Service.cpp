//
// Service.cpp for Service in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Jul 21 02:05:40 2008 caner candan
// Last update Mon Sep 29 19:20:39 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Service.h"
#include "Client.h"
#include "Protocole.h"

Service::Service(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	Service::createWebOffer()
{
  QRegExp	rx;

  if (this->offerWebName->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No name"),
			       tr("No name"));
      this->offerWebName->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->offerWebName->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Name incorrect"),
			       tr("Name incorrect"));
      this->offerWebName->setFocus();
      return;
    }
  if (this->offerWebList->currentRow() < 0)
    {
      QMessageBox::information(this,
			       tr("No offer"),
			       tr("No offer"));
      this->offerWebList->setFocus();
      return;
    }
  if (this->offerWebDomain->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No domain"),
			       tr("No domain"));
      this->offerWebDomain->setFocus();
      return;
    }
  rx.setPattern(PATTERN_DOMAIN);
  if (rx.indexIn(this->offerWebDomain->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Domain incorrect"),
			       tr("Domain incorrect"));
      this->offerWebDomain->setFocus();
      return;
    }
  if (!this->_confirmOffer(this->offerWebList))
    return;
  static_cast<Client*>(this->parent())->createOfferWeb();
}

void	Service::createStreamOffer()
{
  QRegExp	rx;

  if (this->offerStreamName->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No name"),
			       tr("No name"));
      this->offerStreamName->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->offerStreamName->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Name incorrect"),
			       tr("Name incorrect"));
      this->offerStreamName->setFocus();
      return;
    }
  if (this->offerStreamList->currentRow() < 0)
    {
      QMessageBox::information(this,
			       tr("No offer"),
			       tr("No offer"));
      this->offerStreamList->setFocus();
      return;
    }
  if (this->offerStreamTitle->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No title"),
			       tr("No title"));
      this->offerStreamTitle->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->offerStreamTitle->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Title incorrect"),
			       tr("Title incorrect"));
      this->offerStreamTitle->setFocus();
      return;
    }
  if (!this->_confirmOffer(this->offerStreamList))
    return;
  static_cast<Client*>(this->parent())->createOfferStream();
}

void	Service::createWebMore()
{
  QRegExp	rx;

  if (this->webName->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No name"),
			       tr("No name"));
      this->webName->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->webName->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Name incorrect"),
			       tr("Name incorrect"));
      this->webName->setFocus();
      return;
    }
  if (this->webSpace->currentText().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No space"),
			       tr("No space"));
      this->webSpace->setFocus();
      return;
    }
  if (this->webNbDb->currentText().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No nb db"),
			       tr("No nb db"));
      this->webNbDb->setFocus();
      return;
    }
  if (this->webDomain->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No domain"),
			       tr("No domain"));
      this->webDomain->setFocus();
      return;
    }
  rx.setPattern(PATTERN_DOMAIN);
  if (rx.indexIn(this->webDomain->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Domain incorrect"),
			       tr("Domain incorrect"));
      this->webDomain->setFocus();
      return;
    }
  if (!this->_confirmMore(this->webSpace, Protocole::ratioWebSpace,
			  this->webNbDb, Protocole::ratioWebDb))
    return;
  static_cast<Client*>(this->parent())->createWeb();
}

void	Service::createStreamMore()
{
  QRegExp	rx;

  if (this->streamName->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No name"),
			       tr("No name"));
      this->streamName->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->streamName->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Name incorrect"),
			       tr("Name incorrect"));
      this->streamName->setFocus();
      return;
    }
  if (this->streamSlots->currentText().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No slots"),
			       tr("No slots"));
      this->streamSlots->setFocus();
      return;
    }
  if (this->streamBits->currentText().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No bits"),
			       tr("No bits"));
      this->streamBits->setFocus();
      return;
    }
  if (this->streamTitle->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No title"),
			       tr("No title"));
      this->streamTitle->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->streamTitle->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Title incorrect"),
			       tr("Title incorrect"));
      this->streamTitle->setFocus();
      return;
    }
  if (!this->_confirmMore(this->streamSlots, Protocole::ratioStreamSlot,
			  this->streamBits, Protocole::ratioStreamBits))
    return;
  static_cast<Client*>(this->parent())->createStream();
}

void	Service::on_ok_clicked()
{
  if (!this->serviceBox->currentIndex())
    if (!this->webType->currentIndex())
      this->createWebOffer();
    else
      this->createWebMore();
  else
    if (!this->streamType->currentIndex())
      this->createStreamOffer();
    else
      this->createStreamMore();
}

void	Service::on_cancel_clicked()
{
  this->hide();
}

bool	Service::_confirmOffer(QListWidget* list)
{
  Client*	client = static_cast<Client*>(this->parent());

  if (client->creditCurrently->text().toInt()
      < list->currentItem()->data(Qt::UserRole).toInt())
    {
      QMessageBox::information(this,
			       tr("Not enough credit"),
			       tr("Not enough credit"));
      return (false);
    }
  return (QMessageBox::question(this,
				tr("Are you sure ?"),
				tr("Are you sure ?"),
				QMessageBox::Yes | QMessageBox::No)
	  == QMessageBox::Yes);
}

bool	Service::_confirmMore(QComboBox* list1, int ratio1,
			      QComboBox* list2, int ratio2)
{
  Client*	client = static_cast<Client*>(this->parent());

  if (client->creditCurrently->text().toInt()
      < ((list1->currentText().toInt() / ratio1)
	 + (list2->currentText().toInt() / ratio2)))
    {
      QMessageBox::information(this,
			       tr("Not enough credit"),
			       tr("Not enough credit"));
      return (false);
    }
  return (QMessageBox::question(this,
				tr("Are you sure ?"),
				tr("Are you sure ?"),
				QMessageBox::Yes | QMessageBox::No)
	  == QMessageBox::Yes);
}
