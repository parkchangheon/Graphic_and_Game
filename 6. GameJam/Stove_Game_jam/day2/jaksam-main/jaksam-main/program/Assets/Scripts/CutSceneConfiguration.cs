
using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


[Serializable]
[CreateAssetMenu(fileName = "CutSceneConfiguration", menuName = "CutSceneConfiguration", order = 0)]
public class CutSceneConfiguration : ScriptableObject
{
	public List<string> narration;
	public List<Sprite> sprites;
}
