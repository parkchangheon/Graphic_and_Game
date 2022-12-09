using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CollisionHandler : MonoBehaviour
{

    [SerializeField] float levelLoadDelay = 0.5f;
    [SerializeField] AudioClip success;
    [SerializeField] AudioClip crash;

    [SerializeField] ParticleSystem successParticle;
    [SerializeField] ParticleSystem crashParticle;

    AudioSource audioSource;

    bool isTransitioning = false;
    bool collisionDisable = false;


    private void Start()
    {
        audioSource = GetComponent<AudioSource>();

    }


    void Update()
    {
        RespondToDebugKey();
    }

    void RespondToDebugKey()
    {
        if (Input.GetKeyDown(KeyCode.L))
            LoadNextLevel();
        else if (Input.GetKeyDown(KeyCode.C))
            collisionDisable = !collisionDisable;   //Toggle Coliision
    }

    void OnCollisionEnter(Collision collision)
    {
        if (isTransitioning)
            return;

        if (collisionDisable)
            return;

        switch (collision.gameObject.tag)
        {
            case "Friendly":
                Debug.Log("This is Friendly");
                break;

            case "Finish":
                StartSuccessSequence();
                break;

            case "Fuel":
                Debug.Log("You Pick Up Fuel");
                break;

            default:
                StartCrashSequence();
                break;
        }
        
    }

    private void StartSuccessSequence() //Arrive at Finish line
    {
        isTransitioning = true;
        audioSource.Stop();
        audioSource.PlayOneShot(success);
        successParticle.Play();
        GetComponent<movement>().enabled = false;
        Invoke("LoadNextLevel", levelLoadDelay);
    }


    void StartCrashSequence() // didn't arrive at finish line
    {
        isTransitioning = true;
        audioSource.Stop();
        audioSource.PlayOneShot(crash);
        crashParticle.Play();
        GetComponent<movement>().enabled = false;
        Invoke("ReloadLevel", levelLoadDelay);
    }



    void LoadNextLevel()
    {
        int currentSceneIndex = SceneManager.GetActiveScene().buildIndex;
        int nextSceneIndex = currentSceneIndex + 1;
        if(nextSceneIndex == SceneManager.sceneCountInBuildSettings)
        {
            nextSceneIndex = 0;
        }
        SceneManager.LoadScene(nextSceneIndex);
    }

    void ReloadLevel()
    {
        int currentSceneIndex = SceneManager.GetActiveScene().buildIndex;
        SceneManager.LoadScene(currentSceneIndex);
    }

}
