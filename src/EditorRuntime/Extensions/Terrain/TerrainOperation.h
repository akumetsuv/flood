/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#pragma once

#ifdef ENABLE_PLUGIN_TERRAIN

#include "EditorPlugin.h"
#include "UndoOperation.h"
#include "TerrainPlugin.h"
#include "Core/Math/BoundingSphere.h"

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

REFLECT_DECLARE_CLASS(TerrainOperation)

class TerrainOperation : public UndoOperation
{
	REFLECT_DECLARE_OBJECT(TerrainOperation)

public:

	TerrainOperation() {}
	TerrainOperation( TerrainTool::Enum, const RayTriangleQueryResult& );
	
	void undo();
	void redo();
	void ready();

	void updateNormals();
	void loadSaveHeights( std::vector<float>& state, bool save );
	void loadSaveImage( std::vector<byte>& state, bool save );
	
	void applyTool();
	void applyRaiseTool();
	void applyPaintTool();

	void getCellsInRange(const BoundingSphere&, std::vector<CellPtr>& );
	void applyRaiseCell(const BoundingSphere&, const CellPtr& );

	TerrainPtr terrain;
	TerrainTool::Enum tool;
	RayTriangleQueryResult rayQuery;

	// Brush settings.
	int brushSize;
	int brushStrength;
	ImagePtr paintImage;
	ImagePtr brush;
	
	// Tile settings.
	bool tileLock;
	int tileOffsetX;
	int tileOffsetY;

	// Image data.
	std::vector<byte> beforeImage;
	std::vector<byte> afterImage;

	// Heights data.
	std::vector<float> beforeHeights;
	std::vector<float> afterHeights;
};

//-----------------------------------//

NAMESPACE_EDITOR_END

#endif