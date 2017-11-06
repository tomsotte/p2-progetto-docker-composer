#ifndef EDITABLESTRINGLIST_H
#define EDITABLESTRINGLIST_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QList>
#include <QStringList>
#include <vector>
#include <string>

#include "editablestringlistitem.h"

class EditableStringList : public QWidget
{
	Q_OBJECT
public:
	explicit EditableStringList(QWidget *parent = nullptr);

	std::vector<std::string> getStdStringVector() const;

	void addRow(const QString& str = "");
	void setCompleter(QCompleter* value = nullptr);
	void fromStdStringVector(const std::vector<std::string>& v);

private:
	QVBoxLayout* layMain;

	QVBoxLayout* layList;
	QPushButton* btnAddRow;

	QCompleter* completer {nullptr};

	void setupMainLayout();

signals:
	void change();

public slots:
	void onAddRow();
	void onRemoveRow(EditableStringListItem* row);
};

#endif // EDITABLESTRINGLIST_H
