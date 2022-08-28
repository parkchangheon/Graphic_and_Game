using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterSpawn : MonoBehaviour
{
    public Transform[] spawnPoints;
    public GameObject[] MonsterPrefabs;
    public bool currentChar = true;
    public bool IsHit;
    public bool IsHit2;
    float timer;
    float waitingTime;

    // Start is called before the first frame update
    void Start()
    {
        Spawn();
        currentChar = true;
        timer = 0.0f;
        waitingTime = 0.5f;

    }

    public void Spawn()
    {
        Debug.Log("It has Spawn New!");
        int randMon = Random.Range(0, MonsterPrefabs.Length);
        int randSpawn = Random.Range(0, spawnPoints.Length);

        //Instantiate(MonsterPrefabs[0], spawnPoints[randSpawn].position, transform.rotation);
        Instantiate(MonsterPrefabs[randMon], spawnPoints[randSpawn].position, transform.rotation);
    }
}
