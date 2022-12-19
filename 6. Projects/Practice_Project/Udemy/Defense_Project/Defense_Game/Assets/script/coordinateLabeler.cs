using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;

[ExecuteAlways]

public class coordinateLabeler : MonoBehaviour
{
    [SerializeField] Color defaultColor = Color.white;
    [SerializeField] Color blockedColor = Color.gray;

    TextMeshPro label;
    Vector2Int coordinates = new Vector2Int();
    WayPoint waypoint;

    void Awake()
    {
        label = GetComponent<TextMeshPro>();
        label.enabled = false;

        waypoint = GetComponentInParent<WayPoint>();
        DisplayCoordinates();
    }

    void Update()
    {
        if(!Application.isPlaying)
        {
            DisplayCoordinates();
            UpdateObjectName();
        }
        ColorCoordinates();
        ToggleLabels();
    }

    void ColorCoordinates()
    {
        if (waypoint.IsPlaceable)
            label.color = defaultColor;
        else
            label.color = blockedColor;
    }

    void DisplayCoordinates()
    {
        coordinates.x = Mathf.RoundToInt(transform.parent.position.x / UnityEditor.EditorSnapSettings.move.x); //위치를 정수화시켜 반올림.
        coordinates.y = Mathf.RoundToInt(transform.parent.position.z / UnityEditor.EditorSnapSettings.move.z); //여기서는 x,y 좌표지만, 유니티 내에서는 x,z좌표 이기 때문
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
