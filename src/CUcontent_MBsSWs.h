/*
 * CUcontent_MBsSWs.h - Widget for Reading of Measuring Blocks and Switches
 *
 * Copyright (C) 2008-2009 Comer352l
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CUCONTENT_MBSSWS_H
#define CUCONTENT_MBSSWS_H



#include <QtGui>
#include <vector>
#include "ui_CUcontent_MBsSWs.h"
#include "CUcontent_MBsSWs_tableView.h"
#include "AddMBsSWsDlg.h"
#include "SSMprotocol2.h"
#include "libFSSM.h"


class MBSWvalue_dt
{
public:
	MBSWvalue_dt() { rawValue=0; };
	unsigned int rawValue;
	QString scaledStr;
	QString unitStr;
};



class MinMaxMBSWvalue_dt
{
public:
	MinMaxMBSWvalue_dt() { disabled=false; minRawValue=0; minRawValue=0; };
	bool disabled;
	double minRawValue;
	double maxRawValue;
	QString minScaledValueStr;
	QString maxScaledValueStr;
};



class MBSWsettings_dt
{
public:
	MBSWsettings_dt() { timeMode=0; minValuesEnabled=1; maxValuesEnabled=1; };
	bool timeMode;
	bool minValuesEnabled;
	bool maxValuesEnabled;
};



class CUcontent_MBsSWs : public QWidget, private Ui::MBSWcontent_Form
{
	Q_OBJECT

public:
	CUcontent_MBsSWs(QWidget *parent, SSMprotocol2 *SSMP2dev, MBSWsettings_dt options = MBSWsettings_dt());
	~CUcontent_MBsSWs();
	bool setup();
	bool startMBSWreading();
	bool stopMBSWreading();
	bool setMBSWselection(std::vector<MBSWmetadata_dt> MBSWmetaList);
	void getCurrentMBSWselection(std::vector<MBSWmetadata_dt> *MBSWmetaList);
	void getSettings(MBSWsettings_dt *settings);

private:
	SSMprotocol2 *_SSMP2dev;
	QLabel *_MBSWrefreshTimeTitle_label;
	QLabel *_MBSWrefreshTimeValue_label;
	QPushButton *_timemode_pushButton;
	CUcontent_MBsSWs_tableView *_valuesTableView;
	std::vector<mbsw_dt> _supportedMBs;
	std::vector<mbsw_dt> _supportedSWs;
	std::vector<MBSWmetadata_dt> _MBSWmetaList;
	bool _timemode;
	int _lastrefreshduration_ms;
	QList<MBSWvalue_dt> _lastValues;
	QList<MinMaxMBSWvalue_dt> _minmaxData;
	QList<unsigned int> _rawValueIndexes;	/* used to assign the incoming raw values to the MBs/SWs on the (meta-/displayed-) MB/SW-list
						   => NEDED FOR MB/SW-MOVING DURING MB/SW-READING !					*/
	void setupTimeModeUiElements();
	void setupUiFonts();
	void displayMBsSWs();
	void updateTimeInfo(int refreshduration_ms);
	void communicationError(QString addstr);
	void resizeEvent(QResizeEvent *event);

private slots:
	void startstopMBsSWsButtonPressed();
	void callStart();
	void callStop();
	void processMBSWRawValues(std::vector<unsigned int> rawValues, int refreshduration_ms);
	void addMBsSWs();
	void deleteMBsSWs();
	void moveupMBsSWs();
	void movedownMBsSWs();
	void resetMinMax();
	void setDeleteButtonEnabledState();
	void switchTimeMode();

signals:
	void error();

};



#endif
