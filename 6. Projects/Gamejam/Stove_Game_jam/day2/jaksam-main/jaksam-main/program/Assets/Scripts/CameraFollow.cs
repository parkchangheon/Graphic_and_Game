using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    public GameObject Player;
    Vector3 offset = new Vector3(0, 0, -10);
    private void LateUpdate()
    {
        transform.position = Vector3.MoveTowards(transform.position, Player.transform.position + offset, 0.2f);
    }

}
