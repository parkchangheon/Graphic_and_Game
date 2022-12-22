using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;

[ExecuteAlways]
[RequireComponent(typeof(TextMeshPro))]
public class coordinateLabeler : MonoBehaviour
{
    [SerializeField] Color defaultColor = Color.white;
    [SerializeField] Color blockedColor = Color.gray;
    [SerializeField] Color dexploredColor = Color.yellow;
    [SerializeField] Color pathColor = new Color(1f, 0.5f, 0f);
    TextMeshPro label;


    Vector2Int coordinates = new Vector2Int();
    /*WayPoint waypoint;*/
    //=>gridmanager로 대체
    GridManager gridManager;

    void Awake()
    {
        label = GetComponent<TextMeshPro>();
        label.enabled = true;

        /*waypoint = GetComponentInParent<WayPoint>();*/
        gridManager = FindObjectOfType<GridManager>();
        DisplayCoordinates();
    }

    void Update()
    {
        if(!Application.isPlaying)
        {
            DisplayCoordinates();
            UpdateObjectName();
        }
        SetLabelColor();
        ToggleLabels();
    }

    void SetLabelColor()
    {
    /*  if (waypoint.IsPlaceable)
            label.color = defaultColor;
        else
            label.color = blockedColor;*/

        if(gridManager == null) { return; }

        Node node = gridManager.GetNode(coordinates);
        if(node == null) { return; }

        if(!node.isWalkable)
            label.color = blockedColor;

        else if (node.isPath)
            label.color = pathColor;

        else if (node.isExplored)
            label.color = dexploredColor;

        else label.color = defaultColor;
        

    }

    void DisplayCoordinates()
    {
        if(gridManager == null) { return; }
        coordinates.x = Mathf.RoundToInt(transform.parent.position.x / gridManager.UnityGridSize); //위치를 정수화시켜 반올림.
        coordinates.y = Mathf.RoundToInt(transform.parent.position.z / gridManager.UnityGridSize); //여기서는 x,y 좌표지만, 유니티 내에서는 x,z좌표 이기 때문
        label.text = coordinates.x + " , " + coordinates.y;
    }
    void ToggleLabels()
    {
        if(Input.GetKeyDown(KeyCode.C))
        {
            label.enabled = !label.IsActive();
        }
    }

    void UpdateObjectName()
    {
        transform.parent.name = coordinates.ToString();
    }
}
