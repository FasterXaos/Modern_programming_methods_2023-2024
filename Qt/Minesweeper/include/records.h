#pragma once

#include <QFile>
#include <QString>

namespace AED{
	class Records {
		private:
			QFile file = QString("records.txt");

		public:
			Records();
			QString getRecordData();
			void setRecordData(const QString& difficulty, const QString& time);
	};
}
