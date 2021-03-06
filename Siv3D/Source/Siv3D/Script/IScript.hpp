﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Script.hpp>

namespace s3d
{
	class ISiv3DScript
	{
	public:

		static ISiv3DScript* Create();

		virtual ~ISiv3DScript() = default;

		virtual bool init() = 0;

		virtual void shutdown() = 0;

		virtual Script::IDType createFromCode(const String& code, int32 compileOption) = 0;

		virtual Script::IDType createFromFile(const FilePath& path, int32 compileOption) = 0;

		virtual void release(Script::IDType handleID) = 0;

		virtual AngelScript::asIScriptFunction* getFunction(Script::IDType handleID, const String& decl) = 0;

		virtual std::shared_ptr<ScriptModuleData> getModuleData(Script::IDType handleID) = 0;

		virtual bool compiled(Script::IDType handleID) = 0;

		virtual AngelScript::asIScriptEngine* getEngine() = 0;
	};
}
