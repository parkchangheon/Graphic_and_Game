using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectsSpawn : MonoBehaviour
{
    [SerializeField]
    List<GameObject> backgroundObjects;

    [SerializeField]
    Transform playerTrs;

    [SerializeField]
    float spawnDistance;

    [SerializeField]
    float DestroyDistance;

    private void Start()
    {
        for (int i = 0; i < backgroundObjects.Count; i++)
        {
            Vector3 vec = Random.onUnitSphere * Random.Range(spawnDistance, spawnDistance + 3);
            vec.z = 0f;
                backgroundObjects[i].transform.position = playerTrs.position + vec;

        }
    }

    private void Update()
    {
        for (int i = 0; i < backgroundObjects.Count; i++)
        {
            if (Vector2.Distance(playerTrs.position, backgroundObjects[i].transform.position) > DestroyDistance)
            {
                Vector3 vec = Random.onUnitSphere * Random.Range(spawnDistance, spawnDistance + 3);
                vec.z = 0f;
                backgroundObjects[i].transform.position = playerTrs.position + vec;
            }
        }
    }

}
