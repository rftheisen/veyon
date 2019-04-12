/*
 * ComputerControlInterface.h - interface class for controlling a computer
 *
 * Copyright (c) 2017-2019 Tobias Junghans <tobydox@veyon.io>
 *
 * This file is part of Veyon - https://veyon.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#pragma once

#include <QList>
#include <QObject>
#include <QSize>
#include <QTimer>

#include "Computer.h"
#include "Feature.h"
#include "VeyonCore.h"
#include "VncConnection.h"

class QImage;

class FeatureMessage;
class VncConnection;
class VeyonConnection;

class VEYON_CORE_EXPORT ComputerControlInterface : public QObject
{
	Q_OBJECT
public:
	typedef QSharedPointer<ComputerControlInterface> Pointer;

	using State = VncConnection::State;

	ComputerControlInterface( const Computer& computer, QObject* parent = nullptr );
	~ComputerControlInterface() override;

	Pointer weakPointer();

	void start( QSize scaledScreenSize );
	void stop();

	const Computer& computer() const
	{
		return m_computer;
	}

	State state() const
	{
		return m_state;
	}

	const QSize& scaledScreenSize() const
	{
		return m_scaledScreenSize;
	}

	void setScaledScreenSize( QSize size );

	QImage scaledScreen() const;

	QImage screen() const;

	bool hasScreenUpdates() const
	{
		return m_screenUpdated;
	}

	void clearScreenUpdateFlag()
	{
		m_screenUpdated = false;
	}

	const QString& userLoginName() const
	{
		return m_userLoginName;
	}

	void setUserLoginName( const QString& userLoginName );

	const QString& userFullName() const
	{
		return m_userFullName;
	}

	void setUserFullName( const QString& userFullName );

	const FeatureUidList& activeFeatures() const
	{
		return m_activeFeatures;
	}

	void setActiveFeatures( const FeatureUidList& activeFeatures );

	Feature::Uid designatedModeFeature() const
	{
		return m_designatedModeFeature;
	}

	void setDesignatedModeFeature( Feature::Uid designatedModeFeature );

	void sendFeatureMessage( const FeatureMessage& featureMessage );
	bool isMessageQueueEmpty();


private:
	void setScreenUpdateFlag();

	void resetWatchdog();
	void restartConnection();

	void updateState();
	void updateUser();
	void updateActiveFeatures();

	void handleFeatureMessage( const FeatureMessage& message );

	static constexpr int ActiveFeaturesUpdateInterval = 1000;
	static constexpr int UserUpdateInterval = 10000;
	static constexpr int ConnectionWatchdogTimeout = 10000;

	Computer m_computer;

	State m_state;
	QString m_userLoginName;
	QString m_userFullName;
	FeatureUidList m_activeFeatures;
	Feature::Uid m_designatedModeFeature;

	QSize m_scaledScreenSize;

	VncConnection* m_vncConnection;
	VeyonConnection* m_connection;
	QTimer m_connectionWatchdogTimer;

	bool m_screenUpdated;

signals:
	void featureMessageReceived( const FeatureMessage&, ComputerControlInterface::Pointer );
	void userChanged();
	void activeFeaturesChanged();

};

typedef QVector<ComputerControlInterface::Pointer> ComputerControlInterfaceList;
