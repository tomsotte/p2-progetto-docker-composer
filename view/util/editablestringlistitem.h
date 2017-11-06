#ifndef EDITABLESTRINGLISTITEM_H
#define EDITABLESTRINGLISTITEM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCompleter>

class EditableStringListItem : public QWidget
{
	Q_OBJECT
public:
	explicit EditableStringListItem(const QString& str = "", QWidget *parent = nullptr);

	QString getText() const;

	// used to set validator or completers on the edit line
	QLineEdit* getEdtLine() const;

private:
	QIcon icnRemove;

	QHBoxLayout* layMain;
	QPushButton* btnRemove;
	QLineEdit* edtLine;

	void setupMainLayout();

signals:
	void remove(EditableStringListItem*);

public slots:
	void onRemoveClicked();
};

#endif // EDITABLESTRINGLISTITEM_H
