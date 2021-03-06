/*
    Copyright (c) 2010 Stephen Kelly <steveire@gmail.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "kselectionproxymodeltestsuite.h"

#include <QApplication>
#include <QTimer>
#include <QtTest>

#include <kselectionproxymodel.h>

#include "modelselector.h"

//BEGIN NoSelection

/**
  When there is no selection, everything from the source model should be a noop in the proxy.
*/
template<KSelectionProxyModel::FilterBehavior _filterBehaviour>
class TestData<NoSelectionStrategy, _filterBehaviour> : public NoSelectionStrategy
{
public:
    TestData(ProxyModelTest *proxyModelTest)
        : NoSelectionStrategy(proxyModelTest), m_proxyModelTest(proxyModelTest)
    { }

    // If there is no selection, changes in the source model have no effect.
    void noselection_testMoveData()
    {
        QTest::addColumn<SignalList>("signalList");
        QTest::addColumn<PersistentChangeList>("changeList");
        noopTest("move01");
        noopTest("move02");
        noopTest("move03");
        noopTest("move04");
        noopTest("move05");
    }

    KSelectionProxyModel::FilterBehavior filterBehaviour()
    {
        return _filterBehaviour;
    }

    void testInsertWhenEmptyData() Q_DECL_OVERRIDE
    {
        noop_testInsertWhenEmptyData();
    }
    void testInsertInRootData() Q_DECL_OVERRIDE
    {
        noop_testInsertInRootData();
    }
    void testInsertInTopLevelData() Q_DECL_OVERRIDE
    {
        noop_testInsertInTopLevelData();
    }
    void testInsertInSecondLevelData() Q_DECL_OVERRIDE
    {
        noop_testInsertInSecondLevelData();
    }

    void testRemoveFromRootData() Q_DECL_OVERRIDE
    {
        noop_testRemoveFromRootData();
    }
    void testRemoveFromTopLevelData() Q_DECL_OVERRIDE
    {
        noop_testRemoveFromTopLevelData();
    }
    void testRemoveFromSecondLevelData() Q_DECL_OVERRIDE
    {
        noop_testRemoveFromSecondLevelData();
    }

    void testMoveFromRootData() Q_DECL_OVERRIDE
    {
        noselection_testMoveData();
    }
    void testMoveFromTopLevelData() Q_DECL_OVERRIDE
    {
        noselection_testMoveData();
    }
    void testMoveFromSecondLevelData() Q_DECL_OVERRIDE
    {
        noselection_testMoveData();
    }

    void testModifyInRootData() Q_DECL_OVERRIDE
    {
        noop_testModifyInRootData();
    }
    void testModifyInTopLevelData() Q_DECL_OVERRIDE
    {
        noop_testModifyInTopLevelData();
    }
    void testModifyInSecondLevelData() Q_DECL_OVERRIDE
    {
        noop_testModifyInSecondLevelData();
    }

private:
    ProxyModelTest *m_proxyModelTest;
};

//END NoSelection

//BEGIN ImmediateSelectionStrategy

//BEGIN ChildrenOfExactSelection
template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testInsertWhenEmptyData()
{
    noop_testInsertWhenEmptyData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testInsertInRootData()
{
    noop_testInsertInRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testInsertInTopLevelData()
{
    QTest::addColumn<SignalList>("signalList");
    QTest::addColumn<PersistentChangeList>("changeList");

    IndexFinder indexFinder;

    newInsertTest(QStringLiteral("insert01"), indexFinder, 0, 0, 10);
    newInsertTest(QStringLiteral("insert02"), indexFinder, 0, 9, 10);
    newInsertTest(QStringLiteral("insert03"), indexFinder, 10, 10, 10);
    newInsertTest(QStringLiteral("insert04"), indexFinder, 10, 19, 10);
    newInsertTest(QStringLiteral("insert05"), indexFinder, 4, 4, 10);
    newInsertTest(QStringLiteral("insert06"), indexFinder, 4, 13, 10);
    newInsertTest(QStringLiteral("insert07"), indexFinder, 0, 0, 10);
    newInsertTest(QStringLiteral("insert08"), indexFinder, 10, 10, 10);
    newInsertTest(QStringLiteral("insert09"), indexFinder, 4, 4, 10);
    newInsertTest(QStringLiteral("insert10"), indexFinder, 0, 4, 10);
    newInsertTest(QStringLiteral("insert11"), indexFinder, 10, 14, 10);
    newInsertTest(QStringLiteral("insert12"), indexFinder, 4, 8, 10);
    noopTest(QStringLiteral("insert13"));
    noopTest(QStringLiteral("insert14"));
    noopTest(QStringLiteral("insert15"));
    noopTest(QStringLiteral("insert16"));
    noopTest(QStringLiteral("insert17"));
    noopTest(QStringLiteral("insert18"));
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testInsertInSecondLevelData()
{
    noop_testInsertInSecondLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testRemoveFromRootData()
{
    noop_testRemoveFromRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testRemoveFromTopLevelData()
{
    QTest::addColumn<SignalList>("signalList");
    QTest::addColumn<PersistentChangeList>("changeList");

    IndexFinder indexFinder;

    newRemoveTest(QStringLiteral("remove01"), indexFinder, 0, 0, 10);
    newRemoveTest(QStringLiteral("remove02"), indexFinder, 0, 4, 10);
    newRemoveTest(QStringLiteral("remove03"), indexFinder, 9, 9, 10);
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testRemoveFromSecondLevelData()
{
    noop_testRemoveFromSecondLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testMoveFromRootData()
{
    noop_testMoveFromRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testMoveFromTopLevelData()
{
    IndexFinder indexFinder;
    testForwardingMoveData(indexFinder, indexFinder);
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testMoveFromSecondLevelData()
{
    noop_testMoveFromSecondLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testModifyInRootData()
{
    noop_testModifyInRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testModifyInTopLevelData()
{
    QTest::addColumn<SignalList>("signalList");
    QTest::addColumn<PersistentChangeList>("changeList");
    newModifyTest(QStringLiteral("modify01"), IndexFinder(), 0, 0);
    newModifyTest(QStringLiteral("modify02"), IndexFinder(), 0, 4);
    newModifyTest(QStringLiteral("modify03"), IndexFinder(), 9, 9);
    newModifyTest(QStringLiteral("modify04"), IndexFinder(), 6, 9);
    newModifyTest(QStringLiteral("modify05"), IndexFinder(), 4, 4);
    newModifyTest(QStringLiteral("modify06"), IndexFinder(), 3, 7);
    newModifyTest(QStringLiteral("modify07"), IndexFinder(), 0, 9);
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ChildrenOfExactSelection>::testModifyInSecondLevelData()
{
    noop_testModifyInSecondLevelData();
}

//END ChildrenOfExactSelection

//BEGIN ExactSelection
template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testInsertWhenEmptyData()
{
    QTest::addColumn<SignalList>("signalList");
    QTest::addColumn<PersistentChangeList>("changeList");

    IndexFinder indexFinder;

    noopTest(QStringLiteral("insert01"));
    newInsertTest(QStringLiteral("insert02"), indexFinder, 0, 0, 0);
    newInsertTest(QStringLiteral("insert03"), indexFinder, 0, 0, 0);
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testInsertInRootData()
{
    noop_testInsertInRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testInsertInTopLevelData()
{
    noop_testInsertInTopLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testInsertInSecondLevelData()
{
    noop_testInsertInSecondLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testRemoveFromRootData()
{
    noop_testRemoveFromRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testRemoveFromTopLevelData()
{
    noop_testRemoveFromTopLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testRemoveFromSecondLevelData()
{
    noop_testRemoveFromSecondLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testMoveFromRootData()
{
    noop_testMoveFromRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testMoveFromTopLevelData()
{
    noop_testMoveFromTopLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testMoveFromSecondLevelData()
{
    noop_testMoveFromSecondLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testModifyInRootData()
{
    QTest::addColumn<SignalList>("signalList");
    QTest::addColumn<PersistentChangeList>("changeList");
    noopTest(QStringLiteral("modify01"));
    noopTest(QStringLiteral("modify02"));
    noopTest(QStringLiteral("modify03"));
    noopTest(QStringLiteral("modify04"));
    noopTest(QStringLiteral("modify05"));
    newModifyTest(QStringLiteral("modify06"), IndexFinder(), 0, 0);
    newModifyTest(QStringLiteral("modify07"), IndexFinder(), 0, 0);
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testModifyInTopLevelData()
{
    noop_testModifyInTopLevelData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::ExactSelection>::testModifyInSecondLevelData()
{
    noop_testModifyInSecondLevelData();
}

//END ExactSelection

//BEGIN SubTrees
template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testInsertWhenEmptyData()
{
    QTest::addColumn<SignalList>("signalList");
    QTest::addColumn<PersistentChangeList>("changeList");

    IndexFinder indexFinder;

    noopTest(QStringLiteral("insert01"));
    newInsertTest(QStringLiteral("insert02"), indexFinder, 0, 0, 0);
    newInsertTest(QStringLiteral("insert03"), indexFinder, 0, 0, 0);
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testInsertInRootData()
{
    noop_testInsertInRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testInsertInTopLevelData()
{
    testForwardingInsertData(IndexFinder(QList<int>() << 0));
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testInsertInSecondLevelData()
{
    testForwardingInsertData(IndexFinder(QList<int>() << 0 << 5));
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testRemoveFromRootData()
{
    noop_testRemoveFromRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testRemoveFromTopLevelData()
{
    testForwardingRemoveData(IndexFinder(QList<int>() << 0));
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testRemoveFromSecondLevelData()
{
    testForwardingRemoveData(IndexFinder(QList<int>() << 0 << 5));
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testMoveFromRootData()
{
    noop_testMoveFromRootData();
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testMoveFromTopLevelData()
{
    testForwardingMoveData(IndexFinder(QList<int>() << 0), IndexFinder(QList<int>() << 0));
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testMoveFromSecondLevelData()
{
    testForwardingMoveData(IndexFinder(QList<int>() << 0 << 5), IndexFinder(QList<int>() << 0 << 5));
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testModifyInRootData()
{
    QTest::addColumn<SignalList>("signalList");
    QTest::addColumn<PersistentChangeList>("changeList");
    noopTest(QStringLiteral("modify01"));
    noopTest(QStringLiteral("modify02"));
    noopTest(QStringLiteral("modify03"));
    noopTest(QStringLiteral("modify04"));
    noopTest(QStringLiteral("modify05"));
    newModifyTest(QStringLiteral("modify06"), IndexFinder(), 0, 0);
    newModifyTest(QStringLiteral("modify07"), IndexFinder(), 0, 0);
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testModifyInTopLevelData()
{
    testForwardingModifyData(IndexFinder(QList<int>() << 0));
}

template<>
void TestData<ImmediateSelectionStrategy<9>, KSelectionProxyModel::SubTrees>::testModifyInSecondLevelData()
{
    testForwardingModifyData(IndexFinder(QList<int>() << 0 << 5));
}

//END SubTrees

//END ImmediateSelectionStrategy

PROXYMODELTEST_MAIN(SelectionProxyModelTest,
                    SELECTIONPROXYMODELSIMPLETEST(NoSelectionStrategy, KSelectionProxyModel::ChildrenOfExactSelection)
                    SELECTIONPROXYMODELSIMPLETEST(NoSelectionStrategy, KSelectionProxyModel::ExactSelection)
                    SELECTIONPROXYMODELSIMPLETEST(NoSelectionStrategy, KSelectionProxyModel::SubTreeRoots)
                    SELECTIONPROXYMODELSIMPLETEST(NoSelectionStrategy, KSelectionProxyModel::SubTrees)
                    SELECTIONPROXYMODELSIMPLETEST(NoSelectionStrategy, KSelectionProxyModel::SubTreesWithoutRoots)

                    SELECTIONCOMPLETETEST1(ImmediateSelectionStrategy, 9, KSelectionProxyModel::ChildrenOfExactSelection)
                    SELECTIONCOMPLETETEST1(ImmediateSelectionStrategy, 9, KSelectionProxyModel::ExactSelection)
                    SELECTIONCOMPLETETEST1(ImmediateSelectionStrategy, 9, KSelectionProxyModel::SubTrees)
                   )
