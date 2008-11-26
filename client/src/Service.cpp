// Service.cpp --- 
// 
// Filename: Service.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:03:26 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:03:30 2008 (+0200)
//           By: Caner Candan
//     Update #: 1
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

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
      QMessageBox::information(this, tr("no_name"), tr("no_name_txt"));
      this->offerWebName->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->offerWebName->text()) < 0)
    {
      QMessageBox::information(this, tr("name_inc"), tr("name_inc_txt"));
      this->offerWebName->setFocus();
      return;
    }
  if (this->offerWebList->currentRow() < 0)
    {
      QMessageBox::information(this, tr("no_offer"), tr("no_offer_txt"));
      this->offerWebList->setFocus();
      return;
    }
  if (this->offerWebDomain->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_domain"), tr("no_domain_txt"));
      this->offerWebDomain->setFocus();
      return;
    }
  rx.setPattern(PATTERN_DOMAIN);
  if (rx.indexIn(this->offerWebDomain->text()) < 0)
    {
      QMessageBox::information(this, tr("domain_inc"), tr("domain_inc_txt"));
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
      QMessageBox::information(this, tr("no_name"), tr("no_name_txt"));
      this->offerStreamName->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->offerStreamName->text()) < 0)
    {
      QMessageBox::information(this, tr("name_inc"), tr("name_inc_txt"));
      this->offerStreamName->setFocus();
      return;
    }
  if (this->offerStreamList->currentRow() < 0)
    {
      QMessageBox::information(this, tr("no_offer"), tr("no_offer_txt"));
      this->offerStreamList->setFocus();
      return;
    }
  if (this->offerStreamTitle->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_title"), tr("no_title_txt"));
      this->offerStreamTitle->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->offerStreamTitle->text()) < 0)
    {
      QMessageBox::information(this, tr("title_inc"), tr("title_inc_txt"));
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
      QMessageBox::information(this, tr("no_name"), tr("no_name_txt"));
      this->webName->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->webName->text()) < 0)
    {
      QMessageBox::information(this, tr("name_inc"), tr("name_inc_txt"));
      this->webName->setFocus();
      return;
    }
  if (this->webSpace->currentText().isEmpty())
    {
      QMessageBox::information(this, tr("no_space"), tr("no_space_txt"));
      this->webSpace->setFocus();
      return;
    }
  if (this->webNbDb->currentText().isEmpty())
    {
      QMessageBox::information(this, tr("no_nbr_db"), tr("no_nbr_db_txt"));
      this->webNbDb->setFocus();
      return;
    }
  if (this->webDomain->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_domain"), tr("no_domain_txt"));
      this->webDomain->setFocus();
      return;
    }
  rx.setPattern(PATTERN_DOMAIN);
  if (rx.indexIn(this->webDomain->text()) < 0)
    {
      QMessageBox::information(this, tr("domain_inc"), tr("domain_inc_txt"));
      this->webDomain->setFocus();
      return;
    }
  if (!this->_confirmMore(this->webSpace, RATIO_WEB_SPACE,
			  this->webNbDb, RATIO_WEB_DB))
    return;
  static_cast<Client*>(this->parent())->createWeb();
}

void	Service::createStreamMore()
{
  QRegExp	rx;

  if (this->streamName->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_name"), tr("no_name_txt"));
      this->streamName->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->streamName->text()) < 0)
    {
      QMessageBox::information(this, tr("name_inc"), tr("name_inc_txt"));
      this->streamName->setFocus();
      return;
    }
  if (this->streamSlots->currentText().isEmpty())
    {
      QMessageBox::information(this, tr("no_slots"), tr("no_slots_txt"));
      this->streamSlots->setFocus();
      return;
    }
  if (this->streamBits->currentText().isEmpty())
    {
      QMessageBox::information(this, tr("no_bits"), tr("no_bits_txt"));
      this->streamBits->setFocus();
      return;
    }
  if (this->streamTitle->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_title"), tr("no_title_txt"));
      this->streamTitle->setFocus();
      return;
    }
  rx.setPattern(PATTERN_NAME);
  if (rx.indexIn(this->streamTitle->text()) < 0)
    {
      QMessageBox::information(this, tr("title_inc"), tr("title_inc_txt"));
      this->streamTitle->setFocus();
      return;
    }
  if (!this->_confirmMore(this->streamSlots, RATIO_STREAM_SLOT,
			  this->streamBits, RATIO_STREAM_BITS))
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
      QMessageBox::information(this, tr("not_enough_credit"),
			       tr("not_enough_credit_txt"));
      return (false);
    }
  return (QMessageBox::question(this, tr("are_you_sure"),
				tr("are_you_sure_txt"),
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
      QMessageBox::information(this, tr("not_enough_credit"),
			       tr("not_enough_credit_txt"));
      return (false);
    }
  return (QMessageBox::question(this, tr("are_you_sure"),
				tr("are_you_sure_txt"),
				QMessageBox::Yes | QMessageBox::No)
	  == QMessageBox::Yes);
}

// 
// Service.cpp ends here
