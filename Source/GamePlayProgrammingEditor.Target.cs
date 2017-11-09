// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GamePlayProgrammingEditorTarget : TargetRules
{
	public GamePlayProgrammingEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "GamePlayProgramming" } );
	}
}
