using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Enemy))]
public class EnemyHealth : MonoBehaviour
{
    [SerializeField] int maxHitPoints = 5;
    [Tooltip("Adds amount to maxHitpoints when enemy dies")]
    [SerializeField] int difficultyRamp = 1;
    int currentHitPoint = 0;

    Enemy enemy;

    void Start()
    {
        enemy = GetComponent<Enemy>();   
    }

    void OnEnable()
    {
        currentHitPoint = maxHitPoints;
    }

    void OnParticleCollision(GameObject other)
    {
        ProcessHit();    
    }

    void ProcessHit()
    {
        currentHitPoint--;
        if(currentHitPoint<=0)
        {
            gameObject.SetActive(false);
            maxHitPoints += difficultyRamp;
            enemy.RewardGold();
        }
    }

}
