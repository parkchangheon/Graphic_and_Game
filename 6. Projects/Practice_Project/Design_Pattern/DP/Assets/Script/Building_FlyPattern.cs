using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BuildingModel
{
    private Mesh mesh;
    private Texture texture;
}

public class Building_FlyPattern : MonoBehaviour
{
    private BuildingModel BM;
    Vector2 position;

    private void Start()
    {
        position = new Vector2(gameObject.transform.position.x, gameObject.transform.position.y);
        Debug.Log("The Building Position is " + position);
    }
}
