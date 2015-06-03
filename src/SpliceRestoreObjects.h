//////////////////////////////////////////////////////////////////////////
// SpliceRestoreObjects
//
// This file contains implementations of the various undo objects
// we can register with max dealing with KL actions
//
//////////////////////////////////////////////////////////////////////////

#pragma once

// This RAII scopes calls
class HoldActions {
	MSTR m_msg;

public:
	HoldActions(const MCHAR* msg) : m_msg(msg) { theHold.Begin(); }
	~HoldActions() { theHold.Accept(m_msg); }
};

// this static function gives global access to the DFG undo stack
namespace FabricServices {
	namespace Commands {
		class CommandStack;
	}
}
extern FabricServices::Commands::CommandStack*  GetCommandStack();



// This CustomKLUndoRedoCommandObject allows us to merge Max's undo system
// and KL's.  It passes the Undo/Redo commands on to Fabric to to allow it
// to undo/redo it's actions
class CustomKLUndoRedoCommandObject : public RestoreObj
{
	FabricCore::RTVal m_rtval_commands;

public:
	CustomKLUndoRedoCommandObject(FabricCore::RTVal& commands);
	~CustomKLUndoRedoCommandObject();;

	virtual void Restore( int isUndo );
	virtual void Redo();
};

// The PortChange object saves the port structure of a graph
// and can save/restore it to a previous point
class SplicePortChangeObject : public RestoreObj
{
	SpliceTranslationFPInterface* m_maxOwner;

	FabricCore::Variant m_prePortLayout;
	FabricCore::Variant m_postPortLayout;

	// Cache the outport name so we can reconnect if necessary.
	std::string m_outPrePortName;
	std::string m_outPostPortName;

public:
	SplicePortChangeObject(SpliceTranslationFPInterface* maxOwner);
	~SplicePortChangeObject();;

	virtual void EndHold();
	virtual void Restore( int isUndo );
	virtual void Redo();
};

//////////////////////////////////////////////////////////////////////////
// All DFG Commands will add an undo object to maxes queue

class DFGCommandRestoreObj : public RestoreObj
{
	const int m_commandId;

public:
	DFGCommandRestoreObj(int id);
	~DFGCommandRestoreObj();;

	virtual void Restore(int isUndo);
	virtual void Redo();
};