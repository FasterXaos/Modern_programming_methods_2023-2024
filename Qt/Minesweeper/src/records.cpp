#include <QTextStream>

#include "records.h"

namespace AED {
	Records::Records() {
		if (!file.exists()) {
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			QTextStream out(&file);
			out << "Beginner:    \t999s\n"
				   "Intermediate:\t999s\n"
				   "Expert:      \t999s";
			file.close();
		}
	}

	QString Records::getRecordData() {
		QString recordData;
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream in(&file);
			recordData = in.readAll();
			file.close();
		} else {
			recordData = "Beginner:    \t999s\n"
						 "Intermediate:\t999s\n"
						 "Expert:      \t999s";
		}

		return recordData;
	}

	void Records::setRecordData(const QString& difficulty, const QString& time) {
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QStringList lines;
			QTextStream in(&file);
			lines = in.readAll().split('\n');
			file.close();

			int lineIndex = -1;
			if (difficulty == "Beginner") {
				lineIndex = 0;
			} else if (difficulty == "Intermediate") {
				lineIndex = 1;
			} else if (difficulty == "Expert") {
				lineIndex = 2;
			}

			if (lineIndex >= 0 && lineIndex < lines.size()) {
				QStringList lineParts = lines[lineIndex].split('\t');
				lineParts[1] = time;
				lines[lineIndex] = lineParts.join('\t');
			}

			if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
				QTextStream out(&file);
				out << lines.join('\n');
				file.close();
			}
		}
	}
}
